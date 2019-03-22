//
// Created by 田淙宇 on 2019/3/4.
//

#include "Mesh.h"

Mesh::Mesh(Vector<Vertex> vertices, Vector<Index> indices, Vector<Texture> textures,Material material) {
    _vertices=vertices;
    _indices=indices;
    _textures=textures;
    _material=material;
    setupMesh();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1,&_VAO);
    glGenBuffers(1,&_VBO);
    glGenBuffers(1,&_EBO);

    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER,_VBO);
    glBufferData(GL_ARRAY_BUFFER,_vertices.size()*sizeof(Vertex),&_vertices[0],GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,_indices.size()* sizeof(Index),&_indices[0],GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, sizeof(Vertex),(GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex,normal));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex,uv));

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE, sizeof(Vertex),(GLvoid*)offsetof(Vertex,tangent));

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(GLvoid*)offsetof(Vertex,bitangent));

    glBindVertexArray(0);
}

void Mesh::draw(Shader shader) const {
    Index diffuseNum=0;
    Index specularNum=0;
    Index normalNum=1;
    Index heightNum=1;

    for(Index i=0;i<_textures.size();++i){
        glActiveTexture(GL_TEXTURE0+i);

        String num;
        String name=_textures[i].type;
        if(name=="texture_diffuse")
            num="["+std::to_string(diffuseNum++)+"]";
        else if(name=="texture_specular")
            num="["+std::to_string(specularNum++)+"]";
        else if(name=="texture_normal")
            num="["+std::to_string(normalNum++)+"]";
        else if(name=="texture_height")
            num="["+std::to_string(heightNum++)+"]";

        glUniform1i(glGetUniformLocation(shader.ProgramID,(name+num).c_str()),i);
        glBindTexture(GL_TEXTURE_2D,_textures[i].id);
    }
    //std::cout<<"specular:"<<specularNum<<std::endl;
    shader.setInt(diffuseNum,"textureDiffuseSize");
    shader.setInt(specularNum,"textureSpecularSize");
    shader.setVec3(Vec3(_material.ambient),"material.ambient");
    shader.setVec3(Vec3(_material.diffuse),"material.diffuse");
    shader.setVec3(Vec3(_material.specular),"material.specular");
    shader.setFloat(_material.shininess,"material.shininess");
    shader.setFloat(_material.opacity,"material.opacity");
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES,_indices.size(),GL_UNSIGNED_INT,0);
    glBindVertexArray(0);

    glActiveTexture(GL_TEXTURE0);
}