//
// Created by 田淙宇 on 2019/2/26.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <string.h>

#include "TextureLoader.h"
#include "Transform.h"
#include "Camera.h"
#include "Model.h"
#include "ShaderLoader.h"
#include "TestLight.h"
#include "LightManager.h"

LightManager* lightManager;
int width,height;
Shader *shader;
Camera camera;
GLfloat deltaTime=0.0f,lastFrame=0.0f;
GLfloat lastX=400,lastY=300;
PointLight light(1.0,0.09,0.032);
SpotLight *spotLight;
DirLight *dirLight;
bool firstMouse=true;
bool keys[1024];
bool clicked=false;
Model *obj,*obj1;
//static ShaderInfo si{
//        "vertex",
//        "test_fragment"
//};


void keyCall(GLFWwindow* window,int key,int scancode,int action,int mode){
    if(action==GLFW_PRESS)
        keys[key]=true;
    else if(action==GLFW_RELEASE)
        keys[key]=false;
}
void mouseButtonCall(GLFWwindow*window,int button,int action,int mods){
    if(button==GLFW_MOUSE_BUTTON_LEFT)
    {
        if(action==GLFW_PRESS)
            clicked=true;
        else if(action==GLFW_RELEASE)
            clicked=false;
    }
}

void scrollCall(GLFWwindow*window,double xoffset,double yoffset){
    camera.changeFOV(yoffset);
}

void mouseMoveCall(GLFWwindow*window,double xpos,double ypos){
    if(clicked) {
        if (firstMouse) {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;

        camera.rotate(-xoffset,yoffset,0);
    }
    else{
        firstMouse=true;
    }
}

void do_move(){
    GLfloat cameraSpeed=5.0f*deltaTime;
    if(keys[GLFW_KEY_W])
        camera.move(cameraSpeed*camera.front());
    if(keys[GLFW_KEY_S])
        camera.move(cameraSpeed*(-camera.front()));
    if(keys[GLFW_KEY_A])
        camera.move(cameraSpeed*(-camera.right()));
    if(keys[GLFW_KEY_D])
        camera.move(cameraSpeed*(camera.right()));
}

//初始化顶点数据，纹理数据以及着色器
void initShader(){
    lightManager=LightManager::getLightManager();
    ls=new Shader("Vertex","light");
    shader=new Shader("Vertex","test_fragment");
    camera=Camera(glm::vec3(0.0f,0.0f,3.0f));
    //obj=new Model("E:/project/Test/inory/inory.pmx");
    obj1=new Model("E:/project/Test/IA/IAx/IAx.pmx");
    //obj=new Model("e:/project/Test/TDA Ice Cold Append Miku/TDA Ice Cold Append Miku.pmx");
    obj=new Model("e:/project/Test/Tda China Dress Stardust Canary/Tda China Dress Stardust Canary.pmx");
    obj->setPosition(0.0f,-10.0f,0.0f);
    obj->scaleTo(0.2f,0.2f,0.2f);
    obj1->setPosition(20.0f,-10.0f,0.0f);
    obj1->scaleTo(0.1f,0.1f,0.1f);
    InitLight();
    light.setPosition(lightPos);
    light.setAmbient(Vec3(0.05f,0.05f,0.05f));
    light.setDiffuse(Vec3(0.8f,0.8f,0.8f));
    light.setSpecular(lightColor);


    spotLight=new SpotLight(glm::cos(glm::radians(12.5f)),glm::cos(glm::radians(15.0f)),camera.front(),1.0f,0.09f,0.032f,camera.position());
    spotLight->setAmbient(Vec3(0.0f,0.0f,0.0f));
    spotLight->setDiffuse(Vec3(1.0f,1.0f,1.0f));
    spotLight->setSpecular(Vec3(1.0f,1.0f,1.0f));

    dirLight=new DirLight(Vec3(-1.0f,-1.0f,-1.0f),Vec3(0.05f,0.05f,0.05f),Vec3(0.4f,0.4f,0.4f),Vec3(0.5f,0.5f,0.5f));

    //lightManager->addLight(SPOT_LIGHT,spotLight);
    lightManager->addLight(POINT_LIGHT,&light);
    lightManager->addLight(DIR_LIGHT,dirLight);
    lightManager->bindShader(shader);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void display(){
    double time=glfwGetTime();
    spotLight->setDirection(camera.front());
    spotLight->setPosition(camera.position());
    shader->Use();
    shader->setMat4(camera.getProjectionMatrix(),"projection");
    shader->setMat4(camera.getViewMatrix(),"view");

    shader->setFloat(32.0f,"material.shininess");

    shader->setMat4(obj->getModelMatrix(),"model");
    shader->setVec3(camera.position(),"viewPos");

    lightManager->use();

    obj->draw(*shader);

    shader->setMat4(obj1->getModelMatrix(),"model");
    obj1->draw(*shader);

    DrawLight(&camera);
    //obj->rotate(0,0.5f,0);
}

int main() {
    glfwInit();
    //设置opengl版本号：3.3
    //主3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    //次3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    //使用核心模式（禁止旧版函数）
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    //关闭窗口大小可变
    glfwWindowHint(GLFW_RESIZABLE,GL_FALSE);

    GLFWwindow* window=glfwCreateWindow(800,600,"test", nullptr, nullptr);
    if(window== nullptr)
    {
        std::cout<<"fail"<<std::endl;
        //终止
        glfwTerminate();
        return -1;
    }
    //设置为当前线程的上下文
    glfwMakeContextCurrent(window);

    //配合核心模式
    glewExperimental=GL_TRUE;
    if(glewInit()!=GLEW_OK){
        std::cout<<"fail glew"<<std::endl;
        return -1;
    }
    //计算缓冲区(渲染窗口)大小
    glfwGetFramebufferSize(window,&width,&height);
    //设置视口大小
    glViewport(0,0,width,height);

    initShader();
    glfwSetKeyCallback(window,keyCall);
    glfwSetMouseButtonCallback(window,mouseButtonCall);
    glfwSetCursorPosCallback(window,mouseMoveCall);
    glfwSetScrollCallback(window,scrollCall);

    while(!glfwWindowShouldClose(window)){
        //事件检查
        glfwPollEvents();
        do_move();
        glClearColor(0.05f,0.05f,0.05f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        display();
        //交换缓冲区
        glfwSwapBuffers(window);
        GLfloat currentTime=glfwGetTime();
        deltaTime=currentTime-lastFrame;
        lastFrame=currentTime;
    }
    //终止(释放资源)
    glfwTerminate();
    return 0;
}
