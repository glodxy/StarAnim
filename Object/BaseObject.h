//
// Created by 田淙宇 on 2019/4/26.
//

#ifndef TEST_BASEOBJECT_H
#define TEST_BASEOBJECT_H

#include "../Transform.h"
#include "../Loader/ShaderLoader.h"

class BaseObject{
public:
    BaseObject(const String& rootPath){
        _directory=rootPath;
        _shader=NULL;
        _position=Vec3(0,0,0);
    }
    virtual ~BaseObject(){}

    virtual void draw(Shader* shader=NULL)const=0;
    virtual void drawShadow(Shader*shadow)const=0;

    void setPosition(const Vec3& position){
        _position=position;
    }
    void BindShader(Shader *shader){
        _shader=shader;
    }

    virtual Mat4 getModelMatrix()const=0;

protected:
    Shader* _shader=NULL;
    String _directory;
    Vec3 _position;
};

#endif //TEST_BASEOBJECT_H
