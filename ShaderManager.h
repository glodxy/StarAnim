//
// Created by 田淙宇 on 2019/4/26.
//

#ifndef TEST_SHADERMANAGER_H
#define TEST_SHADERMANAGER_H

#include "Transform.h"
#include "Loader/ShaderLoader.h"

void createShader(const String& name,ShaderInfo*s);
void createShader(const String& name,const String& v,const String& f,const String& g=NULL);

/*
 * todo:
 * use smart_ptr to manage Shader's pointer
 * */
class ShaderManager {
public:
    typedef Pair<Shader*> ShaderKey;


    static ShaderManager* getShaderManager();

    void addShader(const String& name,Shader* shader=NULL);

    void removeShader(const String& name);

    void setShader(const String&name,Shader*shader);

    const Shader* getShader(const String& name)const;

    String getShaderName(Shader* shader)const;


private:
    ShaderManager();
    ShaderManager(const ShaderManager& sm);
    static ShaderManager* _shaderManager;
    Map<Shader*> _shaderList;
};


#endif //TEST_SHADERMANAGER_H
