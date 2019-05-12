#version 330 core
layout (location = 0) in vec3 _position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

uniform mat4 lightSpace;
uniform mat4 model;


void main()
{
    gl_Position = lightSpace * model * vec4(_position, 1.0f);
}