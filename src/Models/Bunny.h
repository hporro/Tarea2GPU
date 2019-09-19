#ifndef LEARNOPENGL_BUNNY_H
#define LEARNOPENGL_BUNNY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Texture.h"
#include "../Shader.h"

class Bunny : public Figure {
public:
    Bunny() = default;
    explicit Bunny(glm::vec3 position);

    void translate(glm::vec3 translation);
    void setPos(glm::vec3 position);

    void draw(Shader shader, glm::mat4 projectionTransform, glm::mat4 viewTransform);
protected:
    glm::mat4 modelTransform;
    unsigned int VAO = 0, VBO = 0;
};

Bunny::Bunny(glm::vec3 position) {
    char *bunnyPath = "../resources/bun_zipper_simplified.txt";
    std::ifstream bunnyFile;
    bunnyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        bunnyFile.open(bunnyPath);
        int vertexNumber; bunnyFile >> vertexNumber;
        std::cout << vertexNumber << std::endl;
        bunnyFile.close();
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::BUNNY::Bunny files not found" << std::endl;
    }

}

void Bunny::translate(glm::vec3 translation) {

}

void Bunny::setPos(glm::vec3 position) {

}

void Bunny::draw(Shader shader, glm::mat4 projectionTransform, glm::mat4 viewTransform){

}



#endif //TAREA2_BUNNY_H
