#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosLightSpace;

uniform bool floor=false;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpace;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    TexCoords = texCoords;
    if(floor){
        Normal=vec3(0.0,1.0,0.0);
    }
    else {
        Normal=mat3(transpose(inverse(model)))*normal;
    }
    FragPos=vec3(model*vec4(position,1.0));
    FragPosLightSpace=lightSpace*model*vec4(position,1.0);
}