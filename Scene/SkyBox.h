//
// Created by 田淙宇 on 2019/3/17.
//

#ifndef TEST_SKYBOX_H
#define TEST_SKYBOX_H

#include "BaseScene.h"

class SkyBox {
public:
    SkyBox(const String& baseName,const String&rootPath,size_t verticesSize,float* vertices= nullptr);
    virtual void use()const;
private:
    void setupVAO(float*vertices,size_t verticesSize);
    void loadCubemap(const String&faceName);
    String _directory;
    ID _VAO;
};


#endif //TEST_SKYBOX_H
