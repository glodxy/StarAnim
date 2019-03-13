//
// Created by 田淙宇 on 2019/2/20.
//



#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#ifdef __cplusplus
extern "C"{
#endif

GLuint createTexture(const char* fileName,const std::string& directory){
    std::string file=directory+'/'+std::string(fileName);
    int imgWidth,imgHeight,nrComponents;
    unsigned char* image=stbi_load(file.c_str(),&imgWidth,&imgHeight,&nrComponents,0);

    GLuint texture;
    glGenTextures(1,&texture);

    if(image) {
        GLenum format;
        if(nrComponents==1)
            format=GL_RED;
        else if(nrComponents==3)
            format=GL_RGB;
        else if(nrComponents==4)
            format=GL_RGBA;


        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, image);
        glGenerateMipmap(GL_TEXTURE_2D);

        if(nrComponents==4) {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }else{
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(image);
    }
    else{
        std::cout<<"texture failed to load at:"<<file<<std::endl;
        stbi_image_free(image);
    }
    return texture;
}

#ifdef __cplusplus
};
#endif