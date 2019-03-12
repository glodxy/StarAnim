//
// Created by 田淙宇 on 2019/3/11.
//

#include "DirLight.h"

DirLight::DirLight(const Vec3 &direction, const Vec3 &ambient, const Vec3 &diffuse, const Vec3 &specular):Light(ambient,diffuse,specular),_direction(direction){

}

void DirLight::setDirection(const Vec3 &direction) {
    _direction=direction;
}

void DirLight::use() {
    _shader->setVec3(_ambient,_name+".ambient");
    _shader->setVec3(_diffuse,_name+".diffuse");
    _shader->setVec3(_specular,_name+".specular");
    _shader->setVec3(_direction,_name+".direction");
    _shader->setFloat(1,_name+".flag");
}