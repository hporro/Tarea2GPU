#ifndef TAREA2_MODEL_IMPORTER_H
#define TAREA2_MODEL_IMPORTER_H

#ifndef TINYOBJLOADER_IMPLEMENTATION
#define TINYOBJLOADER_IMPLEMENTATION
#endif

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
    ModelImporter(){}
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
    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
        // Loop over faces(polygon)
        size_t index_offset = 0;
        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
            int fv = shapes[s].mesh.num_face_vertices[f];

            // Loop over vertices in the face.
            for (size_t v = 0; v < fv; v++) {
                // access to vertex
                tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

                tinyobj::real_t vx = attrib.vertices[3*idx.vertex_index+0];
                tinyobj::real_t vy = attrib.vertices[3*idx.vertex_index+1];
                tinyobj::real_t vz = attrib.vertices[3*idx.vertex_index+2];
                tinyobj::real_t nx = attrib.normals[3*idx.normal_index+0];
                tinyobj::real_t ny = attrib.normals[3*idx.normal_index+1];
                tinyobj::real_t nz = attrib.normals[3*idx.normal_index+2];
                tinyobj::real_t tx = attrib.texcoords[2*idx.texcoord_index+0];
                tinyobj::real_t ty = attrib.texcoords[2*idx.texcoord_index+1];

                vertexNormal.push_back((float) vx);
                vertexNormal.push_back((float) vy);
                vertexNormal.push_back((float) vz);

                vertexNormal.push_back((float) nx);
                vertexNormal.push_back((float) ny);
                vertexNormal.push_back((float) nz);

                vertexNormal.push_back((float) tx);
                vertexNormal.push_back((float) ty);
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

    glDrawArrays(GL_TRIANGLES, 0,(vertices.size()/8));
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}

#endif //TAREA2_MODEL_IMPORTER_H
