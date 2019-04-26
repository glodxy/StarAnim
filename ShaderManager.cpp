//
// Created by 田淙宇 on 2019/4/26.
//

#include "ShaderManager.h"

ShaderManager *ShaderManager::_shaderManager=NULL;

ShaderManager::ShaderManager() {
}

ShaderManager::ShaderManager(const ShaderManager &sm) {
    _shaderList=sm._shaderList;
}

ShaderManager* ShaderManager::getShaderManager() {
    if(_shaderManager==NULL)
        _shaderManager=new ShaderManager();
    return _shaderManager;
}

void ShaderManager::addShader(const String &name, Shader *shader) {
    if(_shaderList.find(name)==_shaderList.end())
    {
        _shaderList.insert(ShaderKey(name,shader));
    }
    else{
        std::cout<<"error insert shader:"<<name<<", "<<name<<" existed"<<std::endl;
    }
}


const Shader* ShaderManager::getShader(const String &name) const {
    auto iter=_shaderList.find(name);
    if(iter==_shaderList.end())
    {
        std::cout<<name<<" not existed, get shader error"<<std::endl;
        return NULL;
    }
    return const_cast<const Shader*>(iter->second);
}

void ShaderManager::removeShader(const String &name) {
    auto iter=_shaderList.find(name);
    if(iter==_shaderList.end())
    {
        std::cout<<name<<" not existed, remove error"<<std::endl;
        return;
    }
    else{
        _shaderList.erase(iter);
    }
}

void ShaderManager::setShader(const String &name, Shader *shader) {
    auto iter=_shaderList.find(name);
    if(iter==_shaderList.end())
    {
        std::cout<<name<<" not existed, set error"<<std::endl;
        return;
    }
    iter->second=shader;
}

String ShaderManager::getShaderName(Shader *shader) const {
    for(auto iter=_shaderList.begin();iter!=_shaderList.end();++iter){
        if(iter->second==shader)
            return iter->first;
    }
    return NULL;
}

void createShader(const String& name,ShaderInfo*si){
    Shader *shader=new Shader(si);
    ShaderManager::getShaderManager()->addShader(name,shader);
}

void createShader(const String&name,const String&v,const String&f,const String&g){
    ShaderInfo si{v.c_str(),f.c_str(),g.c_str()};
    Shader* shader=new Shader(&si);
    ShaderManager::getShaderManager()->addShader(name,shader);
}
