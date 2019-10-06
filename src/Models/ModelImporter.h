#ifndef TAREA2_MODEL_IMPORTER_H
#define TAREA2_MODEL_IMPORTER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "../Core/Shader.h"
#include "../Core/Texture.h"

#include "../Model.h"
#include "../objloader.h"

// Imports models, but not working
class ModelImporter : public Model {

public:
    ModelImporter(glm::vec3 position, std::string &inputFile);
    ModelImporter(){}
    void draw(glm::mat4 projectionTransform, glm::mat4 viewTransform);
private:
    GLuint VBOs[3];
    int numTriangles;
};

void ModelImporter::draw(glm::mat4 projectionTransform, glm::mat4 viewTransform){
    shader.setMat4("model", modelTransform);
    shader.setMat4("view", viewTransform);
    shader.setMat4("projection", projectionTransform);

    glDrawArrays(GL_TRIANGLES, 0,numTriangles);
}

ModelImporter::ModelImporter(glm::vec3 position, std::string &inputFile){

    std::vector< glm::vec3 > vertices;
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals; // Won't be used at the moment.

    bool res = loadOBJ(inputFile.c_str(), vertices, uvs, normals);
    if(!res){
        std::cout << "Could not load " << inputFile << " model" << std::endl;
        exit(-1);
    }

    numTriangles = vertices.size()/3;

    modelTransform = glm::mat4(1.0f);
    modelTransform = glm::translate(modelTransform, position);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(3, VBOs);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*uvs.size(), &uvs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(2);
}

#endif //TAREA2_MODEL_IMPORTER_H
