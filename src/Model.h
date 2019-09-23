//
// Created by heini on 17-09-2019.
//

#ifndef TAREA2_MODEL_H
#define TAREA2_MODEL_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "Core/Shader.h"
#include "Core/Texture.h"


class Model {

protected:
    glm::mat4 modelTransform;
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    Shader shader;
    std::vector<Texture> textures;
    std::vector<char *> textureNames;

    void bindTextures();

public:
    virtual void draw(glm::mat4 projectionTransform, glm::mat4 viewTransform) = 0;

    void rotate(float angle, glm::vec3 direction);
    void translate(glm::vec3 translation);
    void setPos(glm::vec3 position);

    void setShader(Shader cubeShader);
    void bind();
    static void unbind();
    void addTexture(Texture tex, char *textureName);
};

void Model::rotate(float angle, glm::vec3 direction) { //angle in radians
    modelTransform = glm::rotate(modelTransform, angle, direction);
}

void Model::translate(glm::vec3 translation){
    modelTransform = glm::translate(modelTransform, translation);
}

void Model::setPos(glm::vec3 position){
    modelTransform = glm::mat4(1.0f);
    modelTransform = glm::translate(modelTransform, position);
}

void Model::setShader(Shader cubeShader) {
    shader = cubeShader;
}

void Model::bind(){
    glBindVertexArray(VAO);
    shader.use();
    bindTextures();
}

void Model::unbind(){
    glBindVertexArray(0);
}

void Model::addTexture(Texture tex, char *textureName) {
    textures.push_back(tex);
    textureNames.push_back(textureName);
}

void Model::bindTextures() { //binds textures and also set them to the shader
    for(int i=0;i<textures.size();i++){
        textures[i].bind(GL_TEXTURE0+i);
        shader.setInt(textureNames[i], i);
    }
}

#endif //TAREA2_MODEL_H
