//
// Created by 田淙宇 on 2019/2/21.
//

#include "Camera.h"

#ifdef __cplusplus
extern "C"{
#endif
Camera::Camera():_fov(45.0f),_pos(0.0f,0.0f,10.0f),origin_front(0.0f,0.0f,-1.0f),origin_up(0.0f,1.0f,0.0f),_right(1.0f,0.0f,0.0f),_yaw(0),_pitch(0),_roll(0),_top_pitch_limit(89),_bot_pitch_limit(-89) {
    _topPitch=_botPitch=false;
    _front=origin_front;
    _up=origin_up;
    _min_fov=1.0f;
    _max_fov=_fov;
}

Camera::Camera(const glm::vec3 &position):Camera() {
    _pos=position;
}

Camera::Camera(const Camera &c) {
    _pos=c._pos;
    _front=c._front;
    _up=c._up;
}

void Camera::move(float x, float y, float z) {
    _pos+=glm::vec3(x,y,z);
}

void Camera::move(const glm::vec3 &direction) {
    _pos+=direction;
}

void Camera::setFOV(float fov) {
    assert(fov>_min_fov&&fov<_max_fov);
    _fov=fov;
}

void Camera::changeFOV(float offset) {
    _fov+=offset*0.5f;
    if(_fov<=_min_fov)
        _fov=_min_fov;
    if(_fov>=_max_fov)
        _fov=_max_fov;
}

void Camera::rotate(float yaw, float pitch, float roll) {
    if(_pitch+pitch>_top_pitch_limit)
    {
        _pitch=_top_pitch_limit;
        _topPitch=true;
    }
    else if(_pitch+pitch<_bot_pitch_limit)
    {
        _pitch=_bot_pitch_limit;
        _botPitch=true;
    }
    else{
        _pitch+=pitch;
        _botPitch=_topPitch=false;
    }
    _yaw=_yaw+yaw>360?_yaw+yaw-360:_yaw+yaw;
    _roll=_roll+roll>360?_roll+roll-360:_roll+roll;

    glm::quat key_quat=glm::quat(glm::vec3(glm::radians(_pitch),glm::radians(_yaw),glm::radians(_roll)));
    glm::mat4 t=glm::mat4_cast(key_quat);
    glm::vec3 new_front=glm::normalize(key_quat*origin_front);
    glm::vec3 new_up=glm::normalize(key_quat*origin_up);
    _front=new_front;
    _up=new_up;
    _right=glm::normalize(glm::cross(_front,_up));
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(_pos,_pos+_front,_up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective<GLfloat>(glm::radians(_fov),(GLfloat)800/600,0.1f,100.0f);
}
#ifdef __cplusplus
};
#endif