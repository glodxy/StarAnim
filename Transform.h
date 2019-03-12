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

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat4 Mat4;
typedef glm::quat Quat;

typedef std::string String;

template <class T>
using Vector=std::vector<T>;


#endif //STARANIM_TRANSFORM_H
