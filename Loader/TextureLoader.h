//
// Created by 田淙宇 on 2019/2/20.
//

#ifndef STARANIM_TEXTURELOADER_H
#define STARANIM_TEXTURELOADER_H


#include "../Transform.h"
#include <GL/glew.h>

#ifdef __cplusplus
extern "C"{
#endif

    GLuint createTexture(const char* fileName,const String& directory);
    GLuint createCubemapByFile(const Vector<String>& faces,const String& directory);
    GLuint createCubemapByName(const String&faceName,const String& directory,IMAGE_FORMAT format);

#ifdef __cplusplus
};
#endif
#endif //STARANIM_TEXTURELOADER_H
