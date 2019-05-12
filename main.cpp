
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include "Loader/ShaderLoader.h"
#include "Loader/TextureLoader.h"
#include "Transform.h"
#include "Camera/Camera.h"

int width,height;
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
GLuint VBO,VAO,EBO,texture,texture2,lightVAO;
glm::mat4 model,view,projection;
Shader shader;
Shader lampShader;
Camera camera;
GLfloat deltaTime=0.0f,lastFrame=0.0f;
GLfloat lastX=400,lastY=300;
bool firstMouse=true;
bool keys[1024];
bool clicked=false;
GLfloat vertices[]={
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f,-1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,0.0f,-1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f,1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,0.0f,1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,0.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,0.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,0.0f,0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,0.0f,0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,0.0f,0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,0.0f,0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,-1.0f,0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,-1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,-1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,-1.0f,0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,-1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,-1.0f,0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f,0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,1.0f,0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,0.0f
};





glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};



static ShaderInfo si{
    "default.vert",
    "fragment"
};
static ShaderInfo ls{
    "default.vert",
    "light_fragment"
};

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
    camera.changeFOV(-yoffset);
    std::cout<<camera.fov()<<std::endl;
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

        GLfloat sensitivity = 0.05f;
        xoffset *= sensitivity;
        yoffset *= sensitivity;
        camera.rotate(-xoffset, yoffset, 0);
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
        camera.move(-cameraSpeed*camera.front());
    if(keys[GLFW_KEY_A])
        camera.move(-glm::normalize(glm::cross(camera.front(),camera.up()))*cameraSpeed);
    if(keys[GLFW_KEY_D])
        camera.move(glm::normalize(glm::cross(camera.front(),camera.up()))*cameraSpeed);
}

//矩阵变化
void transform(int i){
    model=glm::mat4(1.0f);
    model=glm::translate(model,cubePositions[i]);
    model=glm::rotate(model,(GLfloat)glfwGetTime()*1.0f,glm::vec3(0.5f,1.0f,0.0f));
    view=camera.getViewMatrix();
    projection=camera.getProjectionMatrix();
    GLint modelLoc=glGetUniformLocation(shader.ProgramID,"model");
    GLint viewLoc=glGetUniformLocation(shader.ProgramID,"view");
    GLint projectionLoc=glGetUniformLocation(shader.ProgramID,"projection");
    glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));
}
void lightTansform(){
    model=glm::mat4(1.0f);
    model=glm::translate(model,lightPos);
    model=glm::scale(model,glm::vec3(0.2f));
    view=camera.getViewMatrix();
    projection=camera.getProjectionMatrix();
    GLint modelLoc=glGetUniformLocation(lampShader.ProgramID,"model");
    GLint viewLoc=glGetUniformLocation(lampShader.ProgramID,"view");
    GLint projectionLoc=glGetUniformLocation(lampShader.ProgramID,"projection");
    glUniformMatrix4fv(modelLoc,1,GL_FALSE,glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc,1,GL_FALSE,glm::value_ptr(view));
    glUniformMatrix4fv(projectionLoc,1,GL_FALSE,glm::value_ptr(projection));
}
//初始化顶点数据，纹理数据以及着色器
void initShader(){
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&EBO);
    glGenVertexArrays(1,&lightVAO);

    glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER,VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);
        glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8* sizeof(GLfloat),(GLvoid*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,8* sizeof(GLfloat),(GLvoid*)(3* sizeof(GLfloat)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,8* sizeof(GLfloat),(GLvoid*)(5* sizeof(GLfloat)));
        glEnableVertexAttribArray(2);
    glBindVertexArray(0);



    glEnable(GL_DEPTH_TEST);
    shader=Shader(&si);
    lampShader=Shader(&ls);
    camera=Camera();
    texture=createTexture("container.jpg");
    texture2=createTexture("awesomeface.png");
}

void display(int i){
    shader.Use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,texture);
    glUniform1i(glGetUniformLocation(shader.ProgramID,"outTexture"),0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,texture2);
    glUniform1i(glGetUniformLocation(shader.ProgramID,"outTexture2"),1);
    glUniform3f(glGetUniformLocation(shader.ProgramID,"lightColor"),1.0f,1.0f,1.0f);
    glUniform3f(glGetUniformLocation(shader.ProgramID,"lightPos"),lightPos.x,lightPos.y,lightPos.z);
    glUniform3f(glGetUniformLocation(shader.ProgramID,"cameraPos"),camera.position().x,camera.position().y,camera.position().z);
    transform(i);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,36);
    glBindVertexArray(0);
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
        glClearColor(0.2f,0.3f,0.4f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        for(int i=0;i<10;++i)
            display(i);
        lampShader.Use();
        glBindVertexArray(VAO);
        lightTansform();
        glDrawArrays(GL_TRIANGLES,0,36);
        glBindVertexArray(0);
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