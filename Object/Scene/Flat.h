//
// Created by 田淙宇 on 2019/4/8.
//

#ifndef TEST_FLAT_H
#define TEST_FLAT_H


#include "BaseScene.h"



class Flat: public BaseScene{
public:
    Flat(const String &rootPath,float x=10,float y=10);
    void setSize(Vec2 size);
    void setSize(float x,float y);

    void bindCamera(Camera* camera);

    virtual void draw(Shader*shader=NULL)const;
    virtual void drawShadow(Shader* shader)const;

    virtual Mat4 getModelMatrix()const;

    void setLineStrip(bool show);
protected:
    virtual void initVertices();
    //是否显示线框
    bool _show;
    //尺寸
    Vec2 _size;

    void setupWireVAO();
    ID _WireVAO;
    Vector<Vec3> _wireVertices;

private:
    Shader* _wireFrameShader;
    void initWireShader();
    void initGroundShader();


};


#endif //TEST_FLAT_H
