#ifndef LEARNOPENGL_BUNNY_H
#define LEARNOPENGL_BUNNY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Core/Texture.h"
#include "../Core/Shader.h"

#include "../Model.h"

#include "../../libs/tiny_obj_loader.h"

class Bunny : public Model {
public:
    Bunny(glm::vec3 position);
    void draw(glm::mat4 projectionTransform, glm::mat4 viewTransform);
private:
    std::vector<float> loadBunnyModel();
    std::vector<float> vertices;
};

std::vector<float> Bunny::loadBunnyModel() {
    std::string inputfile = "../resources/bunny.obj";
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputfile.c_str());

    if (!warn.empty()) {
        std::cout << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << err << std::endl;
    }

    if (!ret) {
        exit(1);
    }

    std::vector<float> vertexNormal = std::vector<float>();
    for(int i=0;i<(int)shapes[0].mesh.num_face_vertices.size();i++){
        for(int v=0;v<(int)shapes[0].mesh.num_face_vertices[i];v++){
            tinyobj::index_t idx = shapes[0].mesh.indices[v];
            vertexNormal.push_back(attrib.vertices[3*idx.vertex_index+0]);
            vertexNormal.push_back(attrib.vertices[3*idx.vertex_index+1]);
            vertexNormal.push_back(attrib.vertices[3*idx.vertex_index+2]);

            vertexNormal.push_back(attrib.normals[3*idx.normal_index+0]);
            vertexNormal.push_back(attrib.normals[3*idx.normal_index+1]);
            vertexNormal.push_back(attrib.normals[3*idx.normal_index+2]);
        }
    }
    std::cout << vertexNormal.size()/6 << std::endl;
    return vertexNormal;
}

void Bunny::draw(glm::mat4 projectionTransform, glm::mat4 viewTransform){
    shader.setMat4("model", modelTransform);
    shader.setMat4("view", viewTransform);
    shader.setMat4("projection", projectionTransform);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/6);
}

Bunny::Bunny(glm::vec3 position){
    vertices = loadBunnyModel();

    modelTransform = glm::mat4(1.0f);
    modelTransform = glm::translate(modelTransform, position);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices.front(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

#endif //TAREA2_BUNNY_H
