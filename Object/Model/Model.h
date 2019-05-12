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
#include "../BaseObject.h"

class Model:public BaseObject{
public:
    Model(const String& filePath);
    virtual void draw(Shader*shader=NULL)const;
    virtual void drawShadow(Shader*shadow)const;

    virtual void drawNormal(Shader* shader)const;

    void move(float x,float y,float z);
    void setPosition(float x,float y,float z);

    void scaleTo(float xs,float ys,float zs);

    void rotate(float pitch,float yaw,float roll);


    Mat4 getModelMatrix()const;
private:
    Quat _rotation;
    Vec3 _scale;
    Vector<Texture> _textureLoaded;
    Vector<Mesh> _meshes;

    void loadModel(const String& filePath);

    void processNode(aiNode*node,const aiScene* scene);
    Mesh processMesh(aiMesh*mesh,const aiScene*scene);
    Vector<Texture> loadMaterialTextures(aiMaterial*mat,aiTextureType type,const String& typeName);

};


#endif //TEST_MODEL_H
