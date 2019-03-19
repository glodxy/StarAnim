//
// Created by 田淙宇 on 2019/3/17.
//

#include "SkyBox.h"
SkyBox::SkyBox(const String &baseName,const String&rootPath,size_t verticesSize,float* vertices) {
    _directory=rootPath;
    if(vertices== nullptr)
    {
        vertices=&(defaultSkyboxVertices[0]);
        verticesSize=108* sizeof(float);
    }
    loadCubemap("snow");
    setupVAO(vertices,verticesSize);
}

void SkyBox::setupVAO(float *vertices,size_t verticesSize) {
    ID VBO;
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}


