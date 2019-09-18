#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 calcNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c){
    return glm::normalize(glm::cross((b-a),(c-a)));
}

int main(){
    glm::vec3 verticesNormal[] = {
            glm::vec3(-0.5, -0.5, -0.5),
            glm::vec3(0.5, -0.5, -0.5),
            glm::vec3(0.0, -0.5, 0.5),
            glm::vec3(0.0,  0.5,  0.0),
    };

    unsigned int indices[] = {
            0,1,3,
            1,2,3,
            2,0,3,
            0,2,1,
    };

    for(int i=0;i<4;i++){
        glm::vec3 vec = calcNormal(verticesNormal[indices[i*3+0]],verticesNormal[indices[i*3+1]],verticesNormal[indices[i*3+2]]);
        std::cout << "t" << i << ": " << vec.x << ", " << vec.y << ", " << vec.z << "," << std::endl;
    }
}