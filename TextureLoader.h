//
// Created by 田淙宇 on 2019/2/20.
//

#ifndef STARANIM_TEXTURELOADER_H
#define STARANIM_TEXTURELOADER_H



#include <GL/glew.h>
#include <string>
#include <iostream>

#ifdef __cplusplus
extern "C"{
#endif

    GLuint createTexture(const char* fileName,const std::string& directory);


#ifdef __cplusplus
};
#endif
#endif //STARANIM_TEXTURELOADER_H
