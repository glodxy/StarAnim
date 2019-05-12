//
// Created by 田淙宇 on 2019/4/20.
//

#include "RenderManager.h"

RenderManager * RenderManager::renderManager =NULL;

RenderManager* RenderManager::getRenderManager() {
    if(renderManager==NULL)
        renderManager=new RenderManager();
    return renderManager;
}

RenderManager::RenderManager() {}
RenderManager::RenderManager(const RenderManager &r) {
    models=r.models;
    scenes=r.scenes;
}

void RenderManager::addModel(const String &name, Model *model) {
    if(models.find(name)!=models.end())
    {
        std::cout<<"Add Model:"<<name<<" error,"<<name<<" existed!"<<std::endl;
        return;
    }
    models.insert(ModelKey(name,model));
}

void RenderManager::addScene(const String &name, BaseScene *scene) {
    if(scenes.find(name)!=scenes.end())
    {
        std::cout<<"Add Scene:"<<name<<" error,"<<name<<" existed!"<<std::endl;
        return;
    }
    scenes.insert(SceneKey(name,scene));
}

Model* RenderManager::getModel(const String &name) {
    auto iter=models.find(name);
    if(iter==models.end())
        return NULL;
    return iter->second;
}

BaseScene* RenderManager::getScene(const String &name) {
    auto iter=scenes.find(name);
    if(iter==scenes.end())
        return NULL;
    return iter->second;
}

void RenderManager::setModel(const String &name, Model *model) {
    auto iter=models.find(name);
    if(iter==models.end())
    {
        std::cout<<"set model:"<<name<<" error,"<<name<<" not exist"<<std::endl;
        return;
    }
    iter->second=model;
}

void RenderManager::setScene(const String &name, BaseScene *scene) {
    auto iter=scenes.find(name);
    if(iter==scenes.end())
    {
        std::cout<<"set scene:"<<name<<" error,"<<name<<" not exist"<<std::endl;
        return;
    }
    iter->second=scene;
}

void RenderManager::init() {
   glGenFramebuffers(1,&_frameBuffer);
   _width=1024,_height=1024;
   glGenTextures(1,&_frameMap);
   glBindTexture(GL_TEXTURE_2D,_frameMap);
   glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT,_width,_height,0,GL_DEPTH_COMPONENT,GL_FLOAT,NULL);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

   glBindFramebuffer(GL_FRAMEBUFFER,_frameBuffer);
   glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,_frameMap,0);
   glDrawBuffer(GL_NONE);
   glReadBuffer(GL_NONE);
    GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if( result == GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Framebuffer is complete." << std::endl ;
    } else {
        std::cout <<"Framebuffer is not complete." << std::endl ;
    }
   glBindFramebuffer(GL_FRAMEBUFFER,0);

    GLfloat quadVertices[] = {
            // Positions        // Texture Coords
            -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
            1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
            1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
    };
    ID quadVBO;
    // Setup plane VAO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
}

void RenderManager::draw() const {
    Mat4 lightSpace=LightManager::getLightManager()->getLightSpaceMatrix();
    Shader* shader=ShaderManager::getShaderManager()->getShader("default");
    shader->Use();
    shader->setMat4(lightSpace,"lightSpace");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_frameMap);
    shader->setInt(0,"shadowMap");
    for(auto iter=scenes.begin();iter!=scenes.end();++iter){
        if(iter->second!=NULL)
        {
            iter->second->draw(shader);
        }
    }
    for(auto iter=models.begin();iter!=models.end();++iter){
        if(iter->second!=NULL)
        {
            iter->second->draw(shader);
        }
    }
}

void RenderManager::drawShadow() const {
    Shader* shader=ShaderManager::getShaderManager()->getShader("default_shadow");
    shader->Use();
    glViewport(0,0,_width,_height);
    glBindFramebuffer(GL_FRAMEBUFFER,_frameBuffer);
    glClear(GL_DEPTH_BUFFER_BIT);
    Mat4 lightSpace=LightManager::getLightManager()->getLightSpaceMatrix();
    //Mat4 lightSpace=(c->getProjectionMatrix())*(c->getViewMatrix());
    shader->setMat4(lightSpace,"lightSpace");

    for(auto iter=scenes.begin();iter!=scenes.end();++iter){
        if(iter->second!=NULL)
        {
            iter->second->drawShadow(shader);
        }
    }
    for(auto iter=models.begin();iter!=models.end();++iter){
        if(iter->second!=NULL)
        {
            iter->second->drawShadow(shader);
        }
    }

    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void RenderManager::debugShadow() const {
    Shader* debug=ShaderManager::getShaderManager()->getShader("default_shadow_debug");
    debug->Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,_frameMap);
    debug->setInt(0,"depthMap");
    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void RenderManager::debugNormal(Camera *c) const {
    Shader* shader=ShaderManager::getShaderManager()->getShader("default_normal");
    shader->Use();
    shader->setMat4(c->getViewMatrix(),"view");
    shader->setMat4(c->getProjectionMatrix(),"projection");
    for(auto iter=models.begin();iter!=models.end();++iter){
        if(iter->second!=NULL)
        {
            iter->second->drawNormal(shader);
        }
    }
}
