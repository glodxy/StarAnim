//
// Created by 田淙宇 on 2019/3/8.
//
/*
 * Base Class of Light
 * for building kinds of light
 */
#ifndef TEST_LIGHT_H
#define TEST_LIGHT_H

#include "../Loader/ShaderLoader.h"
#include "../Transform.h"

enum LightType{
    IDLE_LIGHT,DIR_LIGHT,POINT_LIGHT,SPOT_LIGHT
};


class Light{
public:
    Light();
    Light(const Vec3&ambient,const Vec3& diffuse,const Vec3& specular);
    virtual ~Light();

    void setAmbient(const Vec3& ambient);
    void setDiffuse(const Vec3& diffuse);
    void setSpecular(const Vec3& specular);

    void setName(const String& name);
    virtual void use(Shader*shader)=0;
protected:
    LightType _type;
    String _name;
    Vec3 _ambient;
    Vec3 _diffuse,_specular;
};
#endif //TEST_LIGHT_H
