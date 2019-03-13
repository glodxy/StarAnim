//
// Created by 田淙宇 on 2019/3/4.
//

#ifndef TEST_MESH_H
#define TEST_MESH_H

#include <iostream>
#include <string>
#include "Transform.h"
#include "ShaderLoader.h"







typedef Vec3 Position;
typedef Vec3 Normal;
typedef Vec2 UV;
typedef Vec3 Tangent;
typedef Vec3 Bitangent;

typedef unsigned int ID;
typedef unsigned int Index;

typedef struct{
    Position position;
    Normal normal;
    UV uv;
    Tangent tangent;
    Bitangent bitangent;
}Vertex;


typedef struct{
    ID id;
    String type;
    String path;
}Texture;

typedef struct{
    Vec4 ambient;
    Vec4 diffuse;
    Vec4 specular;
}Material;

class Mesh {
public:
    Vector<Vertex> _vertices;
    Vector<Index> _indices;
    Vector<Texture> _textures;
    Material _material;
    ID _VAO;

    Mesh(Vector<Vertex> vertices,Vector<Index> indices,Vector<Texture> textures,Material material);

    void draw(Shader shader)const;
protected:
    void setupMesh();
private:
    ID _VBO,_EBO;
};


#endif //TEST_MESH_H
