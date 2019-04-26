//
// Created by 田淙宇 on 2019/4/8.
//

#include "BaseScene.h"


BaseScene::BaseScene(const String & rootPath):BaseObject(rootPath){
    _camera=NULL;
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
