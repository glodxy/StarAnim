//
// Created by 田淙宇 on 2019/4/8.
//

#include "BaseScene.h"

String BaseScene::_directory="";

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

void BaseScene::copyIntoVertices(float *v, size_t size) {
    _vertices.reserve((size)+1);
    _vertices.resize(size);
    memcpy(&_vertices[0],v,sizeof(float)*3*size);
}

void BaseScene::setupVAO() {
    ID VBO;
    glGenVertexArrays(1,&_VAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(Vec3),&_vertices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}
