//
// Created by 田淙宇 on 2019/2/20.
//

#ifndef STARANIM_TRANSFORM_H
#define STARANIM_TRANSFORM_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>



typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat3 Mat3;
typedef glm::mat4 Mat4;
typedef glm::quat Quat;

typedef std::string String;

template <class T>
using Vector=std::vector<T>;

template <class T>
using Map=std::map<String,T>;

template <class T>
using Pair=std::pair<String,T>;

typedef unsigned int ID;
typedef unsigned int Index;


enum IMAGE_FORMAT{tga,jpg,jpeg,png};

static String getFormatStr(IMAGE_FORMAT f){
    switch(f)
    {
        case tga:return ".tga";
        case jpg:return ".jpg";
        case jpeg:return ".jpeg";
        case png:return ".png";
    }
}


class File{
public:
    static String getRootPath();
    static String getShaderPath(const String& shader){
        return "d:/learn/computer-graphic/StarAnim/Shader/"+shader;
    }
};

#endif //STARANIM_TRANSFORM_H
