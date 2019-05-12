//
// Created by 田淙宇 on 2019/3/9.
//

#include <iostream>
#include "PointLight.h"

PointLight::PointLight(float constant, float linear, float quadratic, const Vec3 &ambient, const Vec3 &diffuse,
                       const Vec3 &specular):Light(ambient,diffuse,specular),_constant(constant),_linear(linear),_quadratic(quadratic){
    _type=POINT_LIGHT;
}

void PointLight::setPosition(const Vec3 &position) {
    _position=position;
}

void PointLight::setPosition(float x, float y, float z) {
    _position.x=x;
    _position.y=y;
    _position.z=z;
}

void PointLight::setLightStrenth(float constant, float linear, float quadratic) {
    _constant=constant;
    _linear=linear;
    _quadratic=quadratic;
}

void PointLight::use(Shader*shader) {
    shader->setVec3(_ambient,_name+".base.ambient");
    shader->setVec3(_diffuse,_name+".base.diffuse");
    shader->setVec3(_specular,_name+".base.specular");
    shader->setFloat(_constant,_name+".constant");
    shader->setFloat(_linear,_name+".linear");
    shader->setFloat(_quadratic,_name+".quadratic");
    shader->setVec3(_position,_name+".position");
}