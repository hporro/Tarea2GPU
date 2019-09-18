//
// Created by heini on 17-09-2019.
//

#ifndef TAREA2_TETRAHEDRON_H
#define TAREA2_TETRAHEDRON_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "../Model.h"

namespace TETRAHEDRON {
    float verticesNormal[] = {
        -0.5, -0.5, -0.5, 0, -0.447214, 0.894427,
         0.5, -0.5, -0.5, -0.872872, -0.218218, -0.436436,
         0.0, -0.5, 0.5, 0.872872, -0.218218, -0.436436,
         0.0,  0.5,  0.0, 0, 1, 0,
    };
    unsigned int indices[] = {
        0,1,3,
        1,2,3,
        2,0,3,
        0,2,1,
    };
}

class Tetrahedron : public Model {
public:
    Tetrahedron();
    Tetrahedron(glm::vec3 position);
    void draw(glm::mat4 viewTransform, glm::mat4 projectionTransform);
};

Tetrahedron::Tetrahedron(glm::vec3 position) {
    modelTransform = glm::mat4(1.0f);
    modelTransform = glm::translate(modelTransform, position);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(TETRAHEDRON::verticesNormal), TETRAHEDRON::verticesNormal, GL_STATIC_DRAW);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(TETRAHEDRON::indices), TETRAHEDRON::indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Tetrahedron::Tetrahedron(){
    Tetrahedron(glm::vec3(0.0f,0.0f,0.0f));
}

void Tetrahedron::draw(glm::mat4 viewTransform, glm::mat4 projectionTransform) {
    shader.setMat4("model", modelTransform);
    shader.setMat4("view", viewTransform);
    shader.setMat4("projection", projectionTransform);

    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
}

#endif //TAREA2_TETRAHEDRON_H
