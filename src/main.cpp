#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Core/Shader.h"
#include "Camera/CenteredCamera.h"
#include "Model.h"
#include "Light.h"

#include "Models/Lamp.h"
#include "Models/Cube.h"
#include "Models/Tetrahedron.h"
#include "Models/Piramid.h"
#include "Models/Sphere.h"
#include "Models/ModelImporter.h"

void global_config();
void framebuffer_size_callback(GLFWwindow* glfWwindow, int width, int height);
void mouse_callback(GLFWwindow* glfWwindow, double xpos, double ypos);
void scroll_callback(GLFWwindow* glfWwindow, double xoffset, double yoffset);
void processInput();
void renderModel();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLFWwindow* window;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

//Camera
CenteredCamera camera(glm::vec3(0.0f, 0.0f, 0.0f));

//lighting
Light *currLightN, *currLightM;

glm::vec3 lightPos1(0.00001f, -4.0f, 0.0f);
glm::vec3 lightPos2(0.00001f, 0.0f, -4.0f);

Light l1s[4], l2s[4];

//lights and camera movement parameters
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

//state machine
bool firstChangeModel = true;
bool firstChangeShader = true;
bool firstChangeLightN = true;
bool firstChangeLightM = true;
int modelRendered = 0;
int shaderRendered = 0;
int lightRenderedN = 0;
int lightRenderedM = 0;

//models
Sphere sphere;
Cube cube;
Piramid piramid;
Tetrahedron tet;
ModelImporter sword;

//Shaders
Shader* currShader;
Shader phongShader;
Shader normalMapShader;
Shader toonShader;
Shader shaders[3];

//project-view matrices
glm::mat4 view;
glm::mat4 projection;

int main() {
    global_config();

    sphere = Sphere(glm::vec3(0.0,0.0,0.0));
    cube = Cube(glm::vec3(0.0,0.0,0.0));
    piramid = Piramid(glm::vec3(0.0,0.0,0.0));
    tet = Tetrahedron(glm::vec3(0.0,0.0,0.0));
    std::string path = "../resources/suzanne.obj";
    sword = ModelImporter(glm::vec3(0.0f,0.0f,0.0f),path);

    phongShader = Shader("../src/shaders/phong.vert", "../src/shaders/phong.frag");
    normalMapShader = Shader("../src/shaders/normalMapping.vert", "../src/shaders/normalMapping.frag");
    toonShader = Shader("../src/shaders/toon.vert", "../src/shaders/toon.frag");

    shaders[0] = phongShader;
    shaders[1] = normalMapShader;
    shaders[2] = toonShader;

    Texture text = Texture("../resources/tex.jpg",0,GL_RGB);

    sphere.addTexture(text,"normalMap");
    cube.addTexture(text,"normalMap");
    piramid.addTexture(text,"normalMap");
    tet.addTexture(text,"normalMap");
    sword.addTexture(text,"normalMap");

    currShader = &shaders[shaderRendered];
    sphere.setShader(*currShader);
    cube.setShader(*currShader);
    piramid.setShader(*currShader);
    tet.setShader(*currShader);
    sword.setShader(*currShader);

    Lamp lamp1 = Lamp(lightPos1);
    Shader lampShader1 = Shader("../src/shaders/vertex.vert", "../src/shaders/brightShader.frag");
    lamp1.setShader(lampShader1);

    Lamp lamp2 = Lamp(lightPos2);
    Shader lampShader2 = Shader("../src/shaders/vertex.vert", "../src/shaders/brightShader.frag");
    lamp2.setShader(lampShader2);

    l1s[0] = Light(glm::vec3(1.0,1.0,1.0),glm::vec3(0.2f, 0.2f, 0.2f),glm::vec3(0.5f, 0.5f, 0.5f),glm::vec3(0.9f,0.9f,0.9f));
    l1s[1] = Light(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0f, 0.0f, 0.2f),glm::vec3(0.0f, 0.0f, 0.5f),glm::vec3(0.0f,0.0f,0.9f));
    l1s[2] = Light(glm::vec3(1.0,0.0,0.0),glm::vec3(0.2f, 0.0f, 0.0f),glm::vec3(0.5f, 0.0f, 0.0f),glm::vec3(0.9f,0.0f,0.0f));
    l1s[3] = Light(glm::vec3(0.0,1.0,0.0),glm::vec3(0.0f, 0.2f, 0.0f),glm::vec3(0.0f, 0.5f, 0.0f),glm::vec3(0.0f,0.9f,0.0f));

    l2s[0] = Light(glm::vec3(1.0,1.0,1.0),glm::vec3(0.2f, 0.2f, 0.2f),glm::vec3(0.5f, 0.5f, 0.5f),glm::vec3(0.9f,0.9f,0.9f));
    l2s[1] = Light(glm::vec3(0.0,0.0,1.0),glm::vec3(0.0f, 0.0f, 0.2f),glm::vec3(0.0f, 0.0f, 0.5f),glm::vec3(0.0f,0.0f,0.9f));
    l2s[2] = Light(glm::vec3(1.0,0.0,0.0),glm::vec3(0.2f, 0.0f, 0.0f),glm::vec3(0.5f, 0.0f, 0.0f),glm::vec3(0.9f,0.0f,0.0f));
    l2s[3] = Light(glm::vec3(0.0,1.0,0.0),glm::vec3(0.0f, 0.2f, 0.0f),glm::vec3(0.0f, 0.5f, 0.0f),glm::vec3(0.0f,0.9f,0.0f));

    currLightN = &l1s[0];
    currLightM = &l2s[0];

    while(!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput();

        //glClearColor(0.0f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lamp1.setPos(lightPos1);

        lamp2.setPos(lightPos2);

        projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.2f, 100.0f);

        view = camera.GetViewMatrix();

        renderModel();

        lamp1.bind();
        lampShader1.setVec3("lightColor", currLightN->color);
        lamp1.draw(view, projection);
        lamp1.unbind();

        lamp2.bind();
        lampShader2.setVec3("lightColor", currLightM->color);
        lamp2.draw(view, projection);
        lamp2.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

void processInput(){
    float cameraSpeed = 1.0f * deltaTime;
    float lightSpeed = 1.0f * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(ROLL_OUT, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(ROLL_IN, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        float prevAngle = atan2(lightPos1.y,lightPos1.x);
        float rad = glm::length(glm::vec2(lightPos1.x,lightPos1.y));
        lightPos1.x = rad*cos(prevAngle-lightSpeed);
        lightPos1.y = rad*sin(prevAngle-lightSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        float prevAngle = atan2(lightPos1.y,lightPos1.x);
        float rad = glm::length(glm::vec2(lightPos1.x,lightPos1.y));
        lightPos1.x = rad*cos(prevAngle+lightSpeed);
        lightPos1.y = rad*sin(prevAngle+lightSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        float prevAngle = atan2(lightPos2.z,lightPos2.x);
        float rad = glm::length(glm::vec2(lightPos2.x,lightPos2.z));
        lightPos2.x = rad*cos(prevAngle-lightSpeed);
        lightPos2.z = rad*sin(prevAngle-lightSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        float prevAngle = atan2(lightPos2.z,lightPos2.x);
        float rad = glm::length(glm::vec2(lightPos2.x,lightPos2.z));
        lightPos2.x = rad*cos(prevAngle+lightSpeed);
        lightPos2.z = rad*sin(prevAngle+lightSpeed);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS){
        if(firstChangeModel) {
            modelRendered=(modelRendered+1)%5;
            firstChangeModel = false;
        }
    }else{
        firstChangeModel = true;
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS){
        if(firstChangeShader) {
            shaderRendered=(shaderRendered+1)%3;
            firstChangeShader = false;
            currShader = &shaders[shaderRendered];
        }
    }else{
        firstChangeShader = true;
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS){
        if(firstChangeLightN) {
            lightRenderedN = (lightRenderedN+1)%4;
            firstChangeLightN = false;
            currLightN = &l1s[lightRenderedN];
        }
    }else{
        firstChangeLightN = true;
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
        if(firstChangeLightM) {
            lightRenderedM = (lightRenderedM+1)%4;
            firstChangeLightM = false;
            currLightM = &l2s[lightRenderedM];
        }
    }else{
        firstChangeLightM = true;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS){  // pluss in latinamerican spanish keyboard
        camera.ProcessMouseScroll(0.05);
    }
    if(glfwGetKey(window, GLFW_KEY_SLASH) == GLFW_PRESS){ // minnus in latinamerican spanish keyboard
        camera.ProcessMouseScroll(-0.05);
    }
}

void framebuffer_size_callback(GLFWwindow* glfWwindow, int width, int height){
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* glfWwindow, double xpos, double ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* glfWwindow, double xoffset, double yoffset){
    camera.ProcessMouseScroll(yoffset);
}

void global_config(){
    //glfw window initialization
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Tarea2GPU", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (glewInit()!=GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    //viewport and callbacks setting
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_ENABLED);

    glEnable(GL_DEPTH_TEST);

    //texture wrapping / filtering / mipmapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //uncoment for debugging models
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void renderModel(){

    currShader->use();

    currShader->setVec3("material.ambient", 0.5f, 0.25f, 0.15f);
    currShader->setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
    currShader->setVec3("material.specular", 0.5f, 0.5f, 0.5f);
    currShader->setFloat("material.shininess", 64.0f);

    currShader->setVec3("lights[0].color", currLightN->color);
    currShader->setVec3("lights[0].position", lightPos1);
    currShader->setVec3("lights[0].ambient", currLightN->ambient);
    currShader->setVec3("lights[0].diffuse", currLightN->diffuse);
    currShader->setVec3("lights[0].specular", currLightN->specular);

    currShader->setVec3("lights[1].color", currLightM->color);
    currShader->setVec3("lights[1].position", lightPos2);
    currShader->setVec3("lights[1].ambient", currLightM->ambient);
    currShader->setVec3("lights[1].diffuse", currLightM->diffuse);
    currShader->setVec3("lights[1].specular", currLightM->specular);

    currShader->setVec3("viewPos", camera.getCameraPosition().x,camera.getCameraPosition().y,camera.getCameraPosition().z);

    if(modelRendered == 1){
        sword.setShader(*currShader);
        sword.bind();
        sword.draw(view, projection);
        sword.unbind();
    }

    if(modelRendered == 0){
        sphere.setShader(*currShader);
        sphere.bind();
        sphere.draw(view, projection);
        sphere.unbind();
    }

    if(modelRendered == 2){
        cube.setShader(*currShader);
        cube.bind();
        cube.draw(view, projection);
        cube.unbind();
    }

    if(modelRendered == 3){
        piramid.setShader(*currShader);
        piramid.bind();
        piramid.draw(view, projection);
        piramid.unbind();
    }

    if(modelRendered == 4){
        tet.setShader(*currShader);
        tet.bind();
        tet.draw(view, projection);
        tet.unbind();
    }
}