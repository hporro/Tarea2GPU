//
// Created by heini on 17-09-2019.
//

#ifndef TAREA2_TETRAHEDRON_H
#define TAREA2_TETRAHEDRON_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "../Figure.h"

namespace TETRAHEDRON {
#define SQRT3 1.7320508076
#define SQRT6 2.4494897428
    float verticesNormal[] = {
        -0.5,0.0,-SQRT3/6.0,-0, 0.333333, -0.942809,
        0.5,0.0,-SQRT3/6.0,-0, 0.333333, -0.942809,
        0.0,2*SQRT6/6.0,0,-0, 0.333333, -0.942809,

        0.5,0.0,-SQRT3/6.0,0.816497, 0.333333, 0.471405,
        0.0,0.0,SQRT3/3.0,0.816497, 0.333333, 0.471405,
        0.0,2*SQRT6/6.0,0,0.816497, 0.333333, 0.471405,

        0.0,0.0,SQRT3/3.0,-0.816497, -0.333333, -0.471405,
        -0.5,0.0,-SQRT3/6.0,-0.816497, -0.333333, -0.471405,
        0.0,2*SQRT6/6.0,0,-0.816497, -0.333333, -0.471405,

        0.0,0.0,SQRT3/3.0,-0, -1, -0,
        0.5,0.0,-SQRT3/6.0,-0, -1, -0,
        -0.5,0.0,-SQRT3/6.0,-0, -1, -0,
        
        /*
        -0.5,0.0,-SQRT3/6.0,
        0.5,0.0,-SQRT3/6.0,
        0.0,0.0,SQRT3/3.0,
        0.0,2*SQRT6/6.0,0,
         */
    };
}

class Tetrahedron : public Figure {
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

    glDrawArrays(GL_TRIANGLES, 0, 12);
}

#endif //TAREA2_TETRAHEDRON_H
