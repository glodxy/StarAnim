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
    void setMode(int mode);
protected:
    int _mode;
    bool _show;
    FlatDirection _direction;
    Vec2 _size;

private:
    inline void initVertices(float* vertices);

};


#endif //TEST_FLAT_H
