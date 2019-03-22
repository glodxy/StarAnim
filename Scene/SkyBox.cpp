//
// Created by 田淙宇 on 2019/3/17.
//

#include "SkyBox.h"
SkyBox::SkyBox(const String &baseName,IMAGE_FORMAT format,const String&rootPath,size_t verticesSize,float* vertices):BaseScene() {
    _directory=rootPath;
//    if(vertices== nullptr)
//    {
//        vertices=&(defaultSkyboxVertices[0]);
//        verticesSize=108* sizeof(float);
//    }
    loadCubemap(baseName,format);
    setupVAO(vertices,verticesSize);
    String vs=_directory+"/shader/"+"skybox.vs";
    String fs=_directory+"/shader/"+"skybox.fs";
    _shader=new Shader(vs.c_str(),fs.c_str());
}

void SkyBox::setupVAO(float *vertices,size_t verticesSize) {
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

void SkyBox::loadCubemap(const String &faceName,IMAGE_FORMAT format) {
    _CubeMap=createCubemapByName(faceName,_directory,format);
}

void SkyBox::draw() const {
    glDepthFunc(GL_LEQUAL);
    _shader->Use();
    _shader->setInt(0,"skybox");
    _shader->setMat4(Mat4(Mat3(_camera->getViewMatrix())),"view");
    _shader->setMat4(_camera->getProjectionMatrix(),"projection");
    glBindVertexArray(_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP,_CubeMap);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
}