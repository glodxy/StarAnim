//
// Created by 田淙宇 on 2019/3/10.
//

#ifndef TEST_FLAASHLIGHT_H
#define TEST_FLAASHLIGHT_H

#include "Light.h"

class SpotLight:public Light{
public:
    SpotLight(float innerCutOff,float outerCutOff,const Vec3& direction,
            float constant,float linear,float quadratic,const Vec3& position=Vec3(0,0,0),
            const Vec3& ambient=Vec3(1.0f,1.0f,1.0f),const Vec3& diffuse=Vec3(1.0f,1.0f,1.0f),const Vec3& specular=Vec3(1.0f,1.0f,1.0f));
    virtual ~SpotLight(){}

    virtual void use(Shader* shader);
    void setPosition(const Vec3& position);
    void setDirection(const Vec3& direction);
    void setInnerCutOff(float ic);
    void setOuterCutOff(float oc);
protected:
    Vec3 _position;
    Vec3 _direction;
    float _constant,_linear,_quadratic;
    //内圆锥，外圆锥的余弦
    float _innerCutOff,_outerCutOff;
};


#endif //TEST_FLAASHLIGHT_H
