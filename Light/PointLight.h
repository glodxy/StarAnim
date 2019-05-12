//
// Created by 田淙宇 on 2019/3/9.
//

#ifndef TEST_POINTLIGHT_H
#define TEST_POINTLIGHT_H

#include "Light.h"

class PointLight:public Light{
public:
    PointLight(float constant,float linear,float quadratic,
            const Vec3&ambient=Vec3(1.0f,1.0f,1.0f),const Vec3&diffuse=Vec3(1.0f,1.0f,1.0f),const Vec3& specular=Vec3(1.0f,1.0f,1.0f));


    virtual void use(Shader*shader);
    void setPosition(const Vec3&position);
    void setPosition(float x,float y,float z);
    void setLightStrenth(float constant,float linear,float quadratic);
private:
    Vec3 _position;
    float _constant,_linear,_quadratic;
};


#endif //TEST_POINTLIGHT_H
