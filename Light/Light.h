//
// Created by 田淙宇 on 2019/3/8.
//
/*
 * Base Class of Light
 * for building kinds of light
 */
#ifndef TEST_LIGHT_H
#define TEST_LIGHT_H

#include "../ShaderLoader.h"
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
    void bindShader(Shader* shader);
    void unBindShader();
    virtual void use()=0;
protected:
    LightType _type;
    Shader *_shader;
    String _name;
    Vec3 _ambient,_diffuse,_specular;
};
#endif //TEST_LIGHT_H
