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

    void bindShader(Shader*s);
    void addLight(LightType type,Light* light);

    void use()const;
private:
    LightManager();
    LightManager(const LightManager& lm);
    Shader* _shader;
    static LightManager* _lightManager;
    Vector<Light*> *_lightList;
    int _pointLightCount,_spotLightCount;
};

#endif //TEST_LIGHTMANAGER_H
