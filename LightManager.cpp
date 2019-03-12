//
// Created by 田淙宇 on 2019/3/11.
//

#include "LightManager.h"

LightManager* LightManager::_lightManager=nullptr;

LightManager* LightManager::getLightManager() {
    if(_lightManager==nullptr)
        _lightManager=new LightManager();
    return _lightManager;
}

LightManager::LightManager():_pointLightCount(0),_spotLightCount(0){
    _lightList=new Vector<Light*>();
}

LightManager::LightManager(const LightManager &lm) {
}

LightManager::~LightManager() {
    _lightList->clear();
    delete _lightList;
}

void LightManager::addLight(LightType type, Light *light) {
    String name;
    switch(type){
        case DIR_LIGHT:{
            name="dirLight";
            break;
        }
        case POINT_LIGHT:{
            name="pointLights["+std::to_string(_pointLightCount)+"]";
            ++_pointLightCount;
            break;
        }
        case SPOT_LIGHT:{
            name="spotLights["+std::to_string(_pointLightCount)+"]";
            ++_spotLightCount;
            break;
        }
        default:{
            std::cout<<"light import error"<<std::endl;
            break;
        }
    }
    light->setName(name);
    _lightList->push_back(light);
}

void LightManager::bindShader(Shader *s) {
    _shader=s;
    for(int i=0;i<_lightList->size();++i){
        (*_lightList)[i]->bindShader(s);
    }
}

void LightManager::use() const {
    _shader->setInt(_pointLightCount,"pointLightSize");
    _shader->setInt(_spotLightCount,"spotLightSize");
    for(int i=0;i<_lightList->size();++i){
        (*_lightList)[i]->use();
    }
}