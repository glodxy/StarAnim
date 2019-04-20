//
// Created by 田淙宇 on 2019/4/8.
//

#include "Flat.h"

Flat::Flat(const String& rootPath,float x, float y):BaseScene(rootPath){
    _size.x=x;
    _size.y=y;

    initGroundShader();
    initWireShader();
    initVertices();
    setupWireVAO();
    setupVAO();
}

void Flat::bindCamera(Camera *camera) {
    _camera=camera;
}

void Flat::setSize(Vec2 size) {
    _size=size;
}

void Flat::setSize(float x, float y) {
    _size.x=x;
    _size.y=y;
}

void Flat::setLineStrip(bool show) {
    _show=show;
}

void Flat::initVertices() {
    Vec3 a(1.0f,0.0f,1.0f);
    Vec3 b(1.0f,0.0f,-1.0f);
    Vec3 c(-1.0f,0.0f,1.0f);
    Vec3 d(-1.0f,0.0f,-1.0f);
    _vertices.push_back(a);
    _vertices.push_back(b);
    _vertices.push_back(c);
    _vertices.push_back(d);

    //线框顶点
    for(float i=-1.0;i<=1.0;i+=0.1){
        Vec3 temp(1.0f,0.0f,i);
        Vec3 temp1(-1.0f,0.0f,i);
        _wireVertices.push_back(temp);
        _wireVertices.push_back(temp1);
    }
    for(float i=-1.0;i<=1.0;i+=0.1){
        Vec3 temp(i,0.0f,1.0f);
        Vec3 temp1(i,0.0f,-1.0f);
        _wireVertices.push_back(temp);
        _wireVertices.push_back(temp1);
    }

}
//设置线框VAO
void Flat::setupWireVAO() {
    ID VBO;
    glGenVertexArrays(1,&_WireVAO);
    glGenBuffers(1,&VBO);
    glBindVertexArray(_WireVAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,_wireVertices.size()*sizeof(Vec3),&_wireVertices[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

void Flat::initWireShader() {
    String vs=_directory+"/shader/Ground/grid.vert";
    String fg=_directory+"/shader/Ground/grid.frag";
    _wireFrameShader=new Shader(vs.c_str(),fg.c_str());
}

void Flat::initGroundShader(){
    String vs=_directory+"/Shader/Ground/ground.vert";
    String fg=_directory+"/Shader/Ground/ground.frag";
    _shader=new Shader(vs.c_str(),fg.c_str());
}

void Flat::draw() const {
    _shader->Use();
    Mat4 model(1.0f);
    model=glm::scale(model,Vec3(_size[0],1.0f,_size[1]));
    _shader->setMat4(model,"model");
    _shader->setMat4(_camera->getViewMatrix(),"view");
    _shader->setMat4(_camera->getProjectionMatrix(),"projection");
    _shader->setFloat(_size.x,"xSize");
    _shader->setFloat(_size.y,"ySize");
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLE_STRIP,0,4);
    if(_show) {
        _wireFrameShader->Use();
        _wireFrameShader->setMat4(model,"model");
        _wireFrameShader->setMat4(_camera->getViewMatrix(),"view");
        _wireFrameShader->setMat4(_camera->getProjectionMatrix(),"projection");
        _wireFrameShader->setFloat(_size.x,"xSize");
        _wireFrameShader->setFloat(_size.y,"ySize");
        glBindVertexArray(_WireVAO);
        glDrawArrays(GL_LINES, 0, _wireVertices.size());
    }
    glBindVertexArray(0);
}