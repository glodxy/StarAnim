//
// Created by 田淙宇 on 2019/2/21.
//

#ifndef STARANIM_CAMERA_H
#define STARANIM_CAMERA_H

#include <GL/glew.h>
#include "Transform.h"

#ifdef __cplusplus
extern "C" {
#endif


class Camera {
public:
    Camera();
    Camera(const Camera&);
    Camera(const glm::vec3& position);
    void move(float x,float y,float z);
    void move(const glm::vec3& direction);
    glm::mat4 getViewMatrix()const;
    glm::mat4 getProjectionMatrix()const;

    glm::vec3 front()const{
        return _front;
    }
    glm::vec3 up()const{
        return _up;
    }
    glm::vec3 right()const{
        return _right;
    }
    glm::vec3 position()const{
        return _pos;
    }
    float fov()const{
        return _fov;
    }


    void rotate(float yaw,float pitch,float roll);
    void setFOV(float fov);
    void changeFOV(float offset);
    bool topViewAngle()const{
        return _topPitch;
    }
    bool botViewAngle()const{
        return _botPitch;
    }
private:
    GLfloat _fov,_max_fov,_min_fov;
    bool _topPitch,_botPitch;
    GLfloat _top_pitch_limit,_bot_pitch_limit;
    glm::vec3 _pos,origin_front,origin_up;
    glm::vec3 _front,_up,_right;
    GLfloat _pitch,_yaw,_roll;
};

#ifdef __cplusplus
};
#endif

#endif //STARANIM_CAMERA_H
