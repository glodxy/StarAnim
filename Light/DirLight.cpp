//
// Created by 田淙宇 on 2019/3/11.
//

#include "DirLight.h"

DirLight::DirLight(const Vec3 &direction, const Vec3 &ambient, const Vec3 &diffuse, const Vec3 &specular):Light(ambient,diffuse,specular),_direction(direction){

}

void DirLight::setDirection(const Vec3 &direction) {
    _direction=direction;
}

Vec3 DirLight::getDirection()const{
    return _direction;
}

void DirLight::use(Shader* shader) {
    shader->setVec3(_ambient,_name+".base.ambient");
    shader->setVec3(_diffuse,_name+".base.diffuse");
    shader->setVec3(_specular,_name+".base.specular");
    shader->setVec3(_direction,_name+".direction");
}