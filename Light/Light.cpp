//
// Created by 田淙宇 on 2019/3/9.
//

#include "Light.h"

Light::Light():_ambient(1.0f,1.0f,1.0f),_diffuse(1.0f,1.0f,1.0f),_specular(1.0f,1.0f,1.0f),_type(IDLE_LIGHT){
}

Light::Light(const Vec3 &ambient, const Vec3 &diffuse, const Vec3 &specular):Light(){
    _ambient=ambient;
    _diffuse=diffuse;
    _specular=specular;
}

Light::~Light() {
    _shader=nullptr;
}

void Light::setAmbient(const Vec3 &ambient) {
    _ambient=ambient;
}

void Light::setDiffuse(const Vec3 &diffuse) {
    _diffuse=diffuse;
}

void Light::setSpecular(const Vec3 &specular) {
    _specular=specular;
}

void Light::setName(const String &name) {
    _name=name;
}

void Light::bindShader(Shader *shader) {
    _shader=shader;
}

void Light::unBindShader() {
    _shader=nullptr;
}