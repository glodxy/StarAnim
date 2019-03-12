//
// Created by 田淙宇 on 2019/2/19.
//
#include <iostream>
#include "ShaderLoader.h"
#ifdef __cplusplus
extern "C" {
#endif



/*
 * 读取着色器文件内容，写入内存
 * */
static const GLchar *getShader(const char *fileName) {
    FILE *file = fopen(fileName, "rb");

    if (!file) {
        return NULL;
    }
    //移至文件末尾
    fseek(file, 0, SEEK_END);
    //获取文件长度
    int len = ftell(file);
    //移至文件头
    fseek(file, 0, SEEK_SET);
    //分配目标位置的空间
    GLchar *source = new GLchar[len + 1];
    //读取至source，每次1个字节，读取len次
    fread(source, 1, len, file);
    fclose(file);
    source[len] = 0;

    return const_cast<const GLchar *>(source);
}

GLuint createShader(GLenum shaderType,const char*fileName){
    GLuint shader;
    GLint success;
    GLchar infoLog[512];
    //着色器装载
    shader=glCreateShader(shaderType);
    const GLchar* source=getShader(fileName);
    glShaderSource(shader,1,&source,NULL);
    delete[] source;
    glCompileShader(shader);
    //着色器检查
    glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
    if(!success)
    {
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        switch(shaderType){
            case GL_VERTEX_SHADER:
                std::cout<<"type:vertex shader\n";
                break;
            case GL_FRAGMENT_SHADER:
                std::cout<<"type:fragment shader\n";
                break;
            default:
                break;
        }
        std::cout<<"ERROR:shader compile failed\n"<<infoLog<<std::endl;
        return NULL;
    }
    return shader;
}

GLuint createShaderProgram(ShaderInfo* shader){
    GLuint vertexShader,fragShader,shaderProgram;
    GLint success;
    GLchar infoLog[512];
    //顶点着色器装载
    vertexShader=createShader(GL_VERTEX_SHADER,shader->vertexShader);
    //片段着色器装载
    fragShader=createShader(GL_FRAGMENT_SHADER,shader->fragShader);
    //着色器程序链接
    shaderProgram=glCreateProgram();
    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram,fragShader);
    glLinkProgram(shaderProgram);
    //链接结果检查
    glGetProgramiv(shaderProgram,GL_LINK_STATUS,&success);
    if(!success){
        glGetProgramInfoLog(shaderProgram,512,NULL,infoLog);
        std::cout<<"ERROR:shader link failed\n"<<infoLog<<std::endl;
        return NULL;
    }
    //删除着色器
    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);
    return shaderProgram;
}


Shader::Shader(ShaderInfo *si) {
    ProgramID=createShaderProgram(si);
}

Shader::Shader(const char *v, const char *f) {
    ShaderInfo temp{v,f};
    ProgramID=createShaderProgram(&temp);
}

Shader& Shader::operator=(const Shader &s) {
    this->ProgramID=s.ProgramID;
    return *this;
}

void Shader::Use() {
    glUseProgram(ProgramID);
}

void Shader::setVec2(Vec2 vec, const String& name) {
    glUniform2f(glGetUniformLocation(ProgramID,name.c_str()),vec.x,vec.y);
}

void Shader::setVec3(Vec3 vec, const String &name) {
    glUniform3f(glGetUniformLocation(ProgramID,name.c_str()),vec.x,vec.y,vec.z);
}

void Shader::setMat4(Mat4 mat, const String &name) {
    glUniformMatrix4fv(glGetUniformLocation(ProgramID,name.c_str()),1,GL_FALSE,glm::value_ptr(mat));
}

void Shader::setFloat(float n, const String &name) {
    glUniform1f(glGetUniformLocation(ProgramID,name.c_str()),n);
}

void Shader::setInt(int n, const String &name) {
    glUniform1i(glGetUniformLocation(ProgramID,name.c_str()),n);
}

#ifdef __cplusplus
}
#endif
