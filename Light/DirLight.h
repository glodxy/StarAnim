//
// Created by 田淙宇 on 2019/3/11.
//

#ifndef TEST_DIRLIGHT_H
#define TEST_DIRLIGHT_H

#include "Light.h"

class DirLight:public Light{
public:
    DirLight(const Vec3& direction,
            const Vec3& ambient=Vec3(1.0f,1.0f,1.0f),const Vec3& diffuse=Vec3(1.0f,1.0f,1.0f),const Vec3& specular=Vec3(1.0f,1.0f,1.0f));

    void setDirection(const Vec3& direction);
    virtual void use();
protected:
    Vec3 _direction;
};


#endif //TEST_DIRLIGHT_H
