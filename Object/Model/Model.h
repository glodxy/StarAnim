//
// Created by 田淙宇 on 2019/3/4.
//

#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Mesh.h"
#include "../../Loader/TextureLoader.h"

class Model {
public:
    Model(const String& filePath);
    void draw()const;


    void move(float x,float y,float z);
    void setPosition(float x,float y,float z);
    void setPosition(const Vec3&position);

    void scaleTo(float xs,float ys,float zs);

    void rotate(float pitch,float yaw,float roll);

    void BindShader(Shader*shader);

    Mat4 getModelMatrix()const;
private:
    Vec3 _position;
    Quat _rotation;
    Vec3 _scale;
    Vector<Texture> _textureLoaded;
    Vector<Mesh> _meshes;
    String _directory;
    Shader *_shader;

    void loadModel(const String& filePath);

    void processNode(aiNode*node,const aiScene* scene);
    Mesh processMesh(aiMesh*mesh,const aiScene*scene);
    Vector<Texture> loadMaterialTextures(aiMaterial*mat,aiTextureType type,const String& typeName);

};


#endif //TEST_MODEL_H
