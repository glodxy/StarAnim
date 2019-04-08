//
// Created by 田淙宇 on 2019/3/4.
//

#include "Model.h"

Model::Model(const String &filePath) {
    loadModel(filePath);
    _scale=Vec3(1.0,1.0,1.0);
    _position=Vec3(0,0,0);
    _rotation=Quat(1,0,0,0);
}

void Model::draw(Shader shader) const {
    for(Index i=0;i<_meshes.size();++i){
        _meshes[i].draw(shader);
    }
}

void Model::loadModel(const String &filePath) {
    Assimp::Importer importer;
    const aiScene* scene=importer.ReadFile(filePath,aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene||scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode){
        std::cout<<"ERROR:assimp :"<<importer.GetErrorString()<<std::endl;
        return;
    }

    _directory=filePath.substr(0,filePath.find_last_of('/'));
    processNode(scene->mRootNode,scene);
}

void Model::processNode(aiNode *node, const aiScene *scene) {
    for(Index i=0;i<node->mNumMeshes;++i){
        aiMesh* mesh=scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(processMesh(mesh,scene));
    }
    for(Index i=0;i<node->mNumChildren;++i){
        processNode(node->mChildren[i],scene);
    }
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    Vector<Vertex> vertices;
    Vector<Index> indices;
    Vector<Texture> textures;

    for(Index i=0;i<mesh->mNumVertices;++i){
        Vertex vertex;
        Vec3 vec;
        vec.x=mesh->mVertices[i].x;
        vec.y=mesh->mVertices[i].y;
        vec.z=mesh->mVertices[i].z;
        vertex.position=vec;

        vec.x=mesh->mNormals[i].x;
        vec.y=mesh->mNormals[i].y;
        vec.z=mesh->mNormals[i].z;
        vertex.normal=vec;

        if(mesh->mTextureCoords[0]){
            Vec2 v;
            v.x=mesh->mTextureCoords[0][i].x;
            v.y=mesh->mTextureCoords[0][i].y;
            vertex.uv=v;
        }
        else
            vertex.uv=Vec2(0.0f,0.0f);

        vec.x=mesh->mTangents[i].x;
        vec.y=mesh->mTangents[i].y;
        vec.z=mesh->mTangents[i].z;
        vertex.tangent=vec;

        vec.x=mesh->mBitangents[i].x;
        vec.y=mesh->mBitangents[i].y;
        vec.z=mesh->mBitangents[i].z;
        vertex.bitangent=vec;

        vertices.push_back(vertex);
    }

    for(Index i=0;i<mesh->mNumFaces;++i){
        aiFace face=mesh->mFaces[i];
        for(Index j=0;j<face.mNumIndices;++j){
            indices.push_back(face.mIndices[j]);
        }
    }

    aiMaterial *material=scene->mMaterials[mesh->mMaterialIndex];

    Vector<Texture> diffuseMap=loadMaterialTextures(material,aiTextureType_DIFFUSE,"texture_diffuse");
    textures.insert(textures.end(),diffuseMap.begin(),diffuseMap.end());

    Vector<Texture> specularMap=loadMaterialTextures(material,aiTextureType_SPECULAR,"texture_specular");
    textures.insert(textures.end(),specularMap.begin(),specularMap.end());

    Vector<Texture> normalMap=loadMaterialTextures(material,aiTextureType_NORMALS,"texture_normal");
    textures.insert(textures.end(),normalMap.begin(),normalMap.end());

    Vector<Texture> heightMap=loadMaterialTextures(material,aiTextureType_HEIGHT,"texture_height");
    textures.insert(textures.end(),heightMap.begin(),heightMap.end());


    Material mat;
    aiColor3D color;
    material->Get(AI_MATKEY_COLOR_AMBIENT,color);
    mat.ambient=Vec4(color.r,color.g,color.b,1.0);
    material->Get(AI_MATKEY_COLOR_DIFFUSE,color);
    mat.diffuse=Vec4(color.r,color.g,color.b,1.0);
    material->Get(AI_MATKEY_COLOR_SPECULAR,color);
    mat.specular=Vec4(color.r,color.g,color.b,1.0);
    float shininess;
    if(AI_SUCCESS!=aiGetMaterialFloat(material,AI_MATKEY_SHININESS_STRENGTH,&shininess))
        shininess=0;
    mat.shininess=shininess;
    if(AI_SUCCESS!=aiGetMaterialFloat(material,AI_MATKEY_OPACITY,&shininess))
        shininess=1;
    mat.opacity=shininess;

    return Mesh(vertices,indices,textures,mat);
}

Vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, const String &typeName) {
    Vector<Texture> textures;

//    if(type==aiTextureType_DIFFUSE)
//        std::cout<<"diffuse:"<<mat->GetTextureCount(type)<<std::endl;
    for(Index i=0;i<mat->GetTextureCount(type);++i){
        aiString str;
        mat->GetTexture(type,i,&str);
        //std::cout<<str.C_Str()<<std::endl;
        bool skip=false;
        for(Index j=0;j<_textureLoaded.size();++j){
            if(std::strcmp(_textureLoaded[j].path.data(),str.C_Str())==0){
                textures.push_back(_textureLoaded[j]);
                skip=true;
                break;
            }
        }

        if(!skip){
            Texture texture;
            texture.id=createTexture(str.C_Str(),_directory);
            texture.type=typeName;
            texture.path=str.C_Str();
            textures.push_back(texture);
            _textureLoaded.push_back(texture);
        }
    }
    return textures;
}

void Model::move(float x, float y, float z) {
    _position.x+=x;
    _position.y+=y;
    _position.z+=z;
}

void Model::setPosition(float x, float y, float z) {
    _position.x=x;
    _position.y=y;
    _position.z=z;
}

void Model::setPosition(const Vec3&position) {
    _position=position;
}

void Model::scaleTo(float xs, float ys, float zs) {
    _scale.x=xs;
    _scale.y=ys;
    _scale.z=zs;
}

void Model::rotate(float pitch, float yaw, float roll) {
    Quat temp=glm::quat(glm::vec3(glm::radians(pitch),glm::radians(yaw),glm::radians(roll)));
    _rotation=_rotation*temp;
}

Mat4 Model::getModelMatrix() const {
    Mat4 result(1.0f);
    result=glm::translate(result,_position);
    result=result*glm::mat4_cast(_rotation);
    result=glm::scale(result,_scale);
    return result;
}