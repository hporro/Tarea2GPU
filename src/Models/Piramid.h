#ifndef TAREA2_PIRAMID_H
#define TAREA2_PIRAMID_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "../Model.h"

namespace PIRAMID {
    #define SQRT2 1.4142135624
    float verticesNormal[] = {
        -0.5,0,-0.5,0, 0.57735, -0.816497,   0.0f,  0.0f,
        0.5,0.0,-0.5,0, 0.57735, -0.816497, 1.0f,  0.0f,
        0.0,SQRT2/2.0,0.0,0, 0.57735, -0.816497, 1.0f,  1.0f,

        0.5,0.0,-0.5,0.816497, 0.57735, 0,   0.0f,  0.0f,
        0.5,0.0,0.5,0.816497, 0.57735, 0,1.0f,  0.0f,
        0.0,SQRT2/2.0,0.0,0.816497, 0.57735, 0, 1.0f,  1.0f,

        0.5,0.0,0.5,0, 0.57735, 0.816497,   0.0f,  0.0f,
        -0.5,0.0,0.5,0, 0.57735, 0.816497,1.0f,  0.0f,
        0.0,SQRT2/2.0,0.0,0, 0.57735, 0.816497, 1.0f,  1.0f,

        -0.5,0.0,0.5,-0.816497, 0.57735, 0,   0.0f,  0.0f,
        -0.5,0,-0.5,-0.816497, 0.57735, 0,1.0f,  0.0f,
        0.0,SQRT2/2.0,0.0,-0.816497, 0.57735, 0, 1.0f,  1.0f,

        0.5,0.0,0.5,0, -1, 0,   0.0f,  0.0f,
        0.5,0.0,-0.5,0, -1, 0,1.0f,  0.0f,
        -0.5,0,-0.5,0, -1, 0, 1.0f,  1.0f,

        -0.5,0.0,0.5,0, -1, 0,   0.0f,  0.0f,
        0.5,0.0,0.5,0, -1, 0,1.0f,  0.0f,
        -0.5,0,-0.5,0, -1, 0, 1.0f,  1.0f,
    };
}

class Piramid : public Model {
public:
    Piramid(){}
    Piramid (glm::vec3 position);
    void draw(glm::mat4 viewTransform, glm::mat4 projectionTransform);
};

Piramid::Piramid(glm::vec3 position) {
    modelTransform = glm::mat4(1.0f);
    modelTransform = glm::translate(modelTransform, position);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PIRAMID::verticesNormal), PIRAMID::verticesNormal, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void Piramid::draw(glm::mat4 viewTransform, glm::mat4 projectionTransform) {
    shader.setMat4("model", modelTransform);
    shader.setMat4("view", viewTransform);
    shader.setMat4("projection", projectionTransform);

    glDrawArrays(GL_TRIANGLES, 0, 18);
}

#endif //TAREA2_PIRAMID_H
