//
// Created by 田淙宇 on 2019/4/8.
//

#include "BaseScene.h"

BaseScene::BaseScene(const String & rootPath):_position(0,0,0){
    _camera=NULL;
    _shader=NULL;
    _directory=rootPath;
}

void BaseScene::setPosition(const Vec3& position){
    _position=position;
}

void BaseScene::BindShader(Shader *shader){
    _shader=shader;
}

void BaseScene::BindCamera(Camera *camera){
    _camera=camera;
}

void BaseScene::setupVAO(float *vertices,size_t verticesSize) {
    ID VBO;
    glGenVertexArrays(1,&_VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}
