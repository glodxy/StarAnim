//
// Created by 田淙宇 on 2019/2/19.
//

#ifndef STARANIM_SHADERLOADER_H
#define STARANIM_SHADERLOADER_H

#include <GL/glew.h>
#include <cstdio>
#include "Transform.h"

#ifdef __cplusplus
extern "C"{
#endif

    typedef struct {
        const char* vertexShader;
        const char* fragShader;
    }ShaderInfo;

    class Shader{
    public:
        GLuint ProgramID;
        Shader(){ProgramID=0;}
        explicit Shader(ShaderInfo*);
        explicit Shader(const char*,const char*);
        Shader&operator=(const Shader&s);
        void Use();

        void setVec2(Vec2 vec,const String& name);
        void setVec3(Vec3 vec,const String& name);
        void setMat4(Mat4 mat,const String& name);
        void setFloat(float n,const String& name);
        void setInt(int n,const String& name);
    };
    GLuint createShaderProgram(ShaderInfo*);

#ifdef __cplusplus
};
#endif

#endif//STARANIM_SHADERLOADER_H
