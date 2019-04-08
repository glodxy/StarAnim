//
// Created by 田淙宇 on 2019/4/8.
//

#include "Flat.h"

Flat::Flat(const String& rootPath,FlatDirection direction, float x, float y):BaseScene(rootPath){
    _direction=direction;
    _size.x=x;
    _size.y=y;

    float * vertices=new float[12];
    initVertices(vertices);
    setupVAO(vertices,12);
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

void Flat::setMode(int mode) {
    _mode=mode;
}

void Flat::setLineStrip(bool show) {
    _show=show;
}

void Flat::draw() const {
    _shader->Use();

}