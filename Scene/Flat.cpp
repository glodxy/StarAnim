//
// Created by 田淙宇 on 2019/4/8.
//

#include "Flat.h"

Flat::Flat(const String& rootPath,FlatDirection direction, float x, float y):BaseScene(rootPath){
    _direction=direction;
    _size.x=x;
    _size.y=y;

    initGroundShader();
    if(_wireFrameShader==NULL){
        initWireShader();
    }
    initVertices();
    setupVAO();
}

void Flat::setSize(Vec2 size) {
    _size=size;
}

void Flat::setSize(float x, float y) {
    _size.x=x;
    _size.y=y;
}

void Flat::setDirection(FlatDirection fd) {
    _direction=fd;
}


void Flat::setLineStrip(bool show) {
    _show=show;
}

void Flat::initVertices() {
    Vec3 a(1.0f,1.0f,0.0f);
    Vec3 b(1.0f,-1.0f,0.0f);
    Vec3 c(-1.0f,-1.0f,0.0f);
    Vec3 d(-1.0f,1.0f,0.0f);
    _vertices.push_back(a);
    _vertices.push_back(b);
    _vertices.push_back(c);
    _vertices.push_back(d);
}

void Flat::initWireShader() {
    String vs=_directory+"/shader/Ground/grid.vert";
    String fg=_directory+"/shader/Ground/grid.frag";
    String geo=_directory+"/shader/Ground/grid.geo";
    _wireFrameShader=new Shader(vs.c_str(),fg.c_str());
}

void Flat::initGroundShader(){
    String vs=_directory+"/shader/Ground/ground.vert";
    String fg=_directory+"/shader/Ground/ground.frag";
    _shader=new Shader(vs.c_str(),fg.c_str());
}

void Flat::draw() const {
    _shader->Use();
    _shader->setFloat(_size.x,"xSize");
    _shader->setFloat(_size.y,"ySize");
    _shader->setInt(_direction,"direction");
    glBindVertexArray(_VAO);
    glDrawArrays(GL_TRIANGLES,0,4);
    if(_show) {
        _wireFrameShader->Use();
        _wireFrameShader->setFloat(_blockSize,"blockSize");
        _wireFrameShader->setFloat(_size.x,"xSize");
        _wireFrameShader->setFloat(_size.y,"ySize");
        _wireFrameShader->setInt(_direction,"direction");
        glDrawArrays(GL_POINT, 0, 4);
    }
    glBindVertexArray(0);
}