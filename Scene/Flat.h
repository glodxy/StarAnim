//
// Created by 田淙宇 on 2019/4/8.
//

#ifndef TEST_FLAT_H
#define TEST_FLAT_H


#include "BaseScene.h"

enum FlatDirection{F_UP,F_FRONT,F_RIGHT};


class Flat: public BaseScene{
public:
    Flat(const String &rootPath,FlatDirection direction=F_UP,float x=200,float y=200);
    void setSize(Vec2 size);
    void setSize(float x,float y);

    void setDirection(FlatDirection fd);

    virtual void draw()const;

    void setLineStrip(bool show);
protected:
    virtual void initVertices();
    //是否显示线框
    bool _show;
    //平面朝向
    FlatDirection _direction;
    //平面大小
    Vec2 _size;
    //网格间隔大小
    float _blockSize;

private:
    Shader* _wireFrameShader;
    void initWireShader();
    void initGroundShader();


};


#endif //TEST_FLAT_H
