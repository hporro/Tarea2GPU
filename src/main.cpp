#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"

#include "Models/Lamp.h"
#include "Models/Cube.h"
#include "Models/Tetrahedron.h"
#include "Models/Piramid.h"
#include "Models/Bunny.h"
#include "Models/Sphere.h"
#include "Figure.h"

void global_config();
void framebuffer_size_callback(GLFWwindow* glfWwindow, int width, int height);
void mouse_callback(GLFWwindow* glfWwindow, double xpos, double ypos);
void scroll_callback(GLFWwindow* glfWwindow, double xoffset, double yoffset);
void processInput();

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

GLFWwindow* window;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

Camera camera(glm::vec3(0.0f, 0.0f, 7.0f));

//lighting
glm::vec3 lightPos1(0.0f, 0.0f, 0.0f);
glm::vec3 lightPos2(0.0f, 0.0f, 0.0f);

float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

int main() {
    global_config();

    Sphere fig = Sphere(glm::vec3(0.0f,0.0f,0.0f));
    //fig.rotate(0.4, glm::vec3(0.0,-1.0f,-0.5f));
    Shader phongShader = Shader("../src/shaders/phong.vert", "../src/shaders/phong.frag");
    //fig.setShader(Shader("../src/shaders/vertex.vert","../src/shaders/fragment.frag"));
    fig.setShader(phongShader);

    Lamp lamp1 = Lamp(lightPos1);
    Shader lampShader1 = Shader("../src/shaders/vertex.vert", "../src/shaders/brightShader.frag");
    lamp1.setShader(lampShader1);

    Lamp lamp2 = Lamp(lightPos2);
    Shader lampShader2 = Shader("../src/shaders/vertex.vert", "../src/shaders/brightShader.frag");
    lamp2.setShader(lampShader2);

    while(!glfwWindowShouldClose(window)){
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput();

        //glClearColor(0.0f, 0.4f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        lightPos1.x = cos(glfwGetTime()) * 3.0f;
        lightPos1.y = sin(glfwGetTime()) * 3.0f;
        lamp1.setPos(lightPos1);

        lightPos2.x = cos(glfwGetTime()) * 3.0f;
        lightPos2.z = sin(glfwGetTime()) * 3.0f;
        lamp2.setPos(lightPos2);

        glm::mat4 projection    = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //rotate(0.1,glm::vec3(0.0f,0.0f,1.0f));

        glm::mat4 view = camera.GetViewMatrix();

        fig.bind();

        phongShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        phongShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        phongShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
        phongShader.setFloat("material.shininess", 64.0f);
        phongShader.setVec3("lights[0].position", lightPos1);
        phongShader.setVec3("lights[0].ambient", 0.2f, 0.2f, 0.2f);
        phongShader.setVec3("lights[0].diffuse", 0.5f, 0.5f, 0.5f);
        phongShader.setVec3("lights[0].specular", 1.0f, 1.0f, 1.0f);
        phongShader.setVec3("lights[1].position", lightPos2);
        phongShader.setVec3("lights[1].ambient", 0.2f, 0.2f, 0.2f);
        phongShader.setVec3("lights[1].diffuse", 0.5f, 0.5f, 0.5f);
        phongShader.setVec3("lights[1].specular", 1.0f, 1.0f, 1.0f);
        phongShader.setVec3("viewPos", camera.Position);

        fig.draw(view, projection);
        fig.unbind();

        lamp1.bind();
        lampShader1.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        lamp1.draw(view, projection);
        lamp1.unbind();

        lamp2.bind();
        lampShader2.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
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
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, cameraSpeed);
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

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    //viewport and callbacks setting
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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