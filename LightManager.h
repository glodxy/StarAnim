//
// Created by 田淙宇 on 2019/3/11.
//

#ifndef TEST_LIGHTMANAGER_H
#define TEST_LIGHTMANAGER_H

#include "Light/Light_include.h"
#include <iostream>
class LightManager {
public:
    static LightManager* getLightManager();
    ~LightManager();

    void addLight(LightType type,Light* light);

    DirLight* getDirLight();

    Mat4 getLightSpaceMatrix()const;

    void use(Shader* shader)const;
private:
    LightManager();
    LightManager(const LightManager& lm);
    static LightManager* _lightManager;
    DirLight *_dirLight;
    Vector<Light*> *_lightList;
    int _pointLightCount,_spotLightCount;
};

#endif //TEST_LIGHTMANAGER_H
