//
// Created by 田淙宇 on 2019/4/20.
//

#include "RenderManager.h"

RenderManager * RenderManager::renderManager =NULL;

RenderManager* RenderManager::getRenderManager() {
    if(renderManager==NULL)
        renderManager=new RenderManager();
    return renderManager;
}

RenderManager::RenderManager() {}
RenderManager::RenderManager(const RenderManager &r) {
    models=r.models;
    scenes=r.scenes;
}

void RenderManager::addModel(const String &name, Model *model) {
    if(models.find(name)!=models.end())
    {
        std::cout<<"Add Model:"<<name<<" error,"<<name<<" existed!"<<std::endl;
        return;
    }
    models.insert(ModelKey(name,model));
}

void RenderManager::addScene(const String &name, BaseScene *scene) {
    if(scenes.find(name)!=scenes.end())
    {
        std::cout<<"Add Scene:"<<name<<" error,"<<name<<" existed!"<<std::endl;
        return;
    }
    scenes.insert(SceneKey(name,scene));
}

Model* RenderManager::getModel(const String &name) {
    auto iter=models.find(name);
    if(iter==models.end())
        return NULL;
    return iter->second;
}

BaseScene* RenderManager::getScene(const String &name) {
    auto iter=scenes.find(name);
    if(iter==scenes.end())
        return NULL;
    return iter->second;
}

void RenderManager::setModel(const String &name, Model *model) {
    auto iter=models.find(name);
    if(iter==models.end())
    {
        std::cout<<"set model:"<<name<<" error,"<<name<<" not exist"<<std::endl;
        return;
    }
    iter->second=model;
}

void RenderManager::setScene(const String &name, BaseScene *scene) {
    auto iter=scenes.find(name);
    if(iter==scenes.end())
    {
        std::cout<<"set scene:"<<name<<" error,"<<name<<" not exist"<<std::endl;
        return;
    }
    iter->second=scene;
}

void RenderManager::draw() const {
    for(auto iter=scenes.begin();iter!=scenes.end();++iter){
        if(iter->second!=NULL)
        {
            iter->second->draw();
        }
    }
    for(auto iter=models.begin();iter!=models.end();++iter){
        if(iter->second!=NULL)
        {
            iter->second->draw();
        }
    }
}
