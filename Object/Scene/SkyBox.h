//
// Created by 田淙宇 on 2019/3/17.
//

#ifndef TEST_SKYBOX_H
#define TEST_SKYBOX_H

#include "BaseScene.h"


class SkyBox:public BaseScene{
public:
    SkyBox(const String& baseName/*天空盒图片基础名*/,IMAGE_FORMAT format/*天空盒图片格式*/,const String&rootPath/*天空盒根路径*/,size_t verticesSize=108*sizeof(float),float* vertices= defaultSkyboxVertices);
    virtual void draw(Shader*shader)const;
private:
    void loadCubemap(const String&faceName,IMAGE_FORMAT format);

    ID _CubeMap;
};


#endif //TEST_SKYBOX_H
