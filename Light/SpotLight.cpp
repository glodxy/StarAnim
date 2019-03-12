//
// Created by 田淙宇 on 2019/3/10.
//

#include "SpotLight.h"

SpotLight::SpotLight(float innerCutOff, float outerCutOff, const Vec3 &direction,float constant, float linear,float quadratic, const Vec3 &position,
                       const Vec3 &ambient, const Vec3 &diffuse, const Vec3 &specular):Light(ambient,diffuse,specular),_position(position),_direction(direction),_constant(constant),_linear(linear),_quadratic(quadratic){
    _innerCutOff=innerCutOff;
    _outerCutOff=outerCutOff;
    _type=SPOT_LIGHT;
}

void SpotLight::setPosition(const Vec3 &position) {
    _position=position;
}

void SpotLight::setDirection(const Vec3 &direction) {
    _direction=direction;
}

void SpotLight::setInnerCutOff(float ic) {
    _innerCutOff=ic;
}

void SpotLight::setOuterCutOff(float oc) {
    _outerCutOff=oc;
}

void SpotLight::use() {
    _shader->setVec3(_ambient,_name+".ambient");
    _shader->setVec3(_diffuse,_name+".diffuse");
    _shader->setVec3(_specular,_name+".specular");

    _shader->setVec3(_position,_name+".position");

    _shader->setVec3(_direction,_name+".direction");
    _shader->setFloat(_innerCutOff,_name+".innercutoff");
    _shader->setFloat(_outerCutOff,_name+".outercutoff");

    _shader->setFloat(_constant,_name+".constant");
    _shader->setFloat(_linear,_name+".linear");
    _shader->setFloat(_quadratic,_name+".quadratic");

    _shader->setFloat(0,_name+".flag");
}