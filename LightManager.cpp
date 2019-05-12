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
            light->setName(name);
            _dirLight=(DirLight*)light;
            return;
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

DirLight * LightManager::getDirLight() {
    if(_dirLight==NULL){
        std::cout<<"error get direct light, light not exist"<<std::endl;
        return NULL;
    }
    return _dirLight;
}



Mat4 LightManager::getLightSpaceMatrix() const {
    Vec3 dir=_dirLight->getDirection();
    dir*=10.0;
    Mat4 lightView=glm::lookAt(-dir, glm::vec3(0,0,0), glm::vec3(0,1.0,0));
    Mat4 lightProjection=glm::ortho(-10.0f,10.0f,-10.0f,10.0f,1.0f,50.0f);
    return (lightProjection*lightView);
}

void LightManager::use(Shader* shader) const {
    shader->setInt(_pointLightCount,"pointLightSize");
    shader->setInt(_spotLightCount,"spotLightSize");
    _dirLight->use(shader);
    for(int i=0;i<_lightList->size();++i){
        (*_lightList)[i]->use(shader);
    }
}