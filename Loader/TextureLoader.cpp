//
// Created by 田淙宇 on 2019/2/20.
//



#include "TextureLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"
#ifdef __cplusplus
extern "C"{
#endif

GLuint createTexture(const char* fileName,const String& directory){
    String file=directory+'/'+String(fileName);
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

GLuint createCubemapByName(const String& faceName,const String& directory,IMAGE_FORMAT format){
    Vector<String> temp(6);
    String f=getFormatStr(format);
    temp[0]=faceName+"_rt"+f;
    temp[1]=faceName+"_lf"+f;
    temp[2]=faceName+"_up"+f;
    temp[3]=faceName+"_dn"+f;
    temp[4]=faceName+"_bk"+f;
    temp[5]=faceName+"_ft"+f;

    return createCubemapByFile(temp,directory);
}

GLuint createCubemapByFile(const Vector<String>&faces,const String& directory){
    GLuint ID;
    glGenTextures(1,&ID);
    glBindTexture(GL_TEXTURE_CUBE_MAP,ID);

    int imgWidth,imgHeight,nrComponents;
    for(int i=0;i<faces.size();++i){
        String file=directory+'/'+faces[i];
        unsigned char* image=stbi_load(file.c_str(),&imgWidth,&imgHeight,&nrComponents,0);
        if(image){
            GLenum format;
            if(nrComponents==1)
                format=GL_RED;
            else if(nrComponents==3)
                format=GL_RGB;
            else if(nrComponents==4)
                format=GL_RGBA;

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, format, imgWidth, imgHeight, 0, format, GL_UNSIGNED_BYTE, image);
            stbi_image_free(image);
        }
        else
        {
            std::cout << "Cubemap texture failed to load at path: " << file << std::endl;
            stbi_image_free(image);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return ID;
}

#ifdef __cplusplus
};
#endif