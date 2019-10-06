#ifndef TAREA2_LIGHT_H
#define TAREA2_LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Light{
    glm::vec3 color, ambient, diffuse, specular;
    Light(glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : color(color), ambient(ambient), diffuse(diffuse), specular(specular) {}
    Light(){}
};

#endif //TAREA2_LIGHT_H
