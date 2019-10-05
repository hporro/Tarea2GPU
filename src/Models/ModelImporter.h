#ifndef TAREA2_MODEL_IMPORTER_H
#define TAREA2_MODEL_IMPORTER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include "../Core/Shader.h"
#include "../Core/Texture.h"

#include "../Model.h"

#include "../../libs/tiny_obj_loader.h"

// Imports models, but not working
class ModelImporter : public Model {

public:
    ModelImporter(glm::vec3 position, std::string &inputFile);
    void draw(glm::mat4 projectionTransform, glm::mat4 viewTransform);
private:
    std::vector<float> loadModel(std::string &inputFile);
    std::vector<float> vertices;
};

std::vector<float> ModelImporter::loadModel(std::string &inputFile) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;

    std::string warn;
    std::string err;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, inputFile.c_str());

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
    for(int s=0;s<(int)shapes.size();s++) {
        size_t index_offset = 0;
        for (int i = 0; i < (int) shapes[s].mesh.num_face_vertices.size(); i++) {
            int fv = shapes[s].mesh.num_face_vertices[i];
            for (int v = 0; v < (int) fv; v++) {
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                vertexNormal.push_back((float) attrib.vertices[3 * idx.vertex_index + 0]);
                vertexNormal.push_back((float) attrib.vertices[3 * idx.vertex_index + 1]);
                vertexNormal.push_back((float) attrib.vertices[3 * idx.vertex_index + 2]);

                vertexNormal.push_back((float) attrib.normals[3 * idx.normal_index + 0]);
                vertexNormal.push_back((float) attrib.normals[3 * idx.normal_index + 1]);
                vertexNormal.push_back((float) attrib.normals[3 * idx.normal_index + 2]);

                //vertexNormal.push_back((float) attrib.texcoords[2 * idx.texcoord_index + 0]);
                //vertexNormal.push_back((float) attrib.texcoords[2 * idx.texcoord_index + 1]);
            }
            index_offset += fv;
        }
    }
    return vertexNormal;
}

void ModelImporter::draw(glm::mat4 projectionTransform, glm::mat4 viewTransform){
    shader.setMat4("model", modelTransform);
    shader.setMat4("view", viewTransform);
    shader.setMat4("projection", projectionTransform);

    glDrawArrays(GL_TRIANGLES, 0,(vertices.size()/6));
}

ModelImporter::ModelImporter(glm::vec3 position, std::string &inputFile){
    vertices = loadModel(inputFile);

    modelTransform = glm::mat4(1.0f);
    modelTransform = glm::translate(modelTransform, position);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    //glEnableVertexAttribArray(2);

}

#endif //TAREA2_MODEL_IMPORTER_H
