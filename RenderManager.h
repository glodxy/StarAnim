//
// Created by 田淙宇 on 2019/4/20.
//

#ifndef TEST_RENDERMANAGER_H
#define TEST_RENDERMANAGER_H

#include "Object/Object_include.h"
#include "ShaderManager.h"
#include "LightManager.h"

/*
 * todo:
 * 优化shader与object关联存储方式
 * */
class RenderManager {
public:
    typedef Pair<Model*> ModelKey;
    typedef Pair<BaseScene*> SceneKey;

    static RenderManager* getRenderManager();
    void addModel(const String& name,Model* model=NULL);
    Model* getModel(const String&name);

    void addScene(const String& name,BaseScene* scene=NULL);
    BaseScene* getScene(const String& name);

    void setModel(const String& name,Model* model);
    void setScene(const String& name,BaseScene* scene);

    void setSize(int w,int h);

    void init();

    void draw()const;
    void drawShadow()const;

    void debugNormal(Camera *c)const;

    void debugShadow()const;
private:

    RenderManager();
    RenderManager(const RenderManager& r);
    static RenderManager *renderManager;
    int _width,_height;
    ID _frameBuffer,_frameMap;
    ID quadVAO;
    Map<BaseScene*> scenes;
    Map<Model*> models;
};


#endif //TEST_RENDERMANAGER_H
