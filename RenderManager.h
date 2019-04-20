//
// Created by 田淙宇 on 2019/4/20.
//

#ifndef TEST_RENDERMANAGER_H
#define TEST_RENDERMANAGER_H

#include "Object/Object_include.h"

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

    void draw()const;
private:
    RenderManager();
    RenderManager(const RenderManager& r);
    static RenderManager *renderManager;
    Map<BaseScene*> scenes;
    Map<Model*> models;

};


#endif //TEST_RENDERMANAGER_H
