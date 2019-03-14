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

void PointLight::use() {
    _shader->setVec3(_ambient,_name+".ambient");
    _shader->setVec3(_diffuse,_name+".diffuse");
    _shader->setVec3(_specular,_name+".specular");
    _shader->setFloat(_constant,_name+".constant");
    _shader->setFloat(_linear,_name+".linear");
    _shader->setFloat(_quadratic,_name+".quadratic");
    _shader->setVec3(_position,_name+".position");
}