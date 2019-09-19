#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.1415

glm::vec3 calcNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c){
    return -glm::normalize(glm::cross((b-a),(c-a)));
}

int main(){
#define SQRT3 1.7320508076
#define SIN60 0.8660254038
#define SIN30 0.5
#define SQRT2 1.4142135624
#define SQRT6 2.4494897428

    glm::vec3 verticesNormal[] = {
            glm::vec3(-0.5,0.0,-SQRT3/6.0),
            glm::vec3(0.5,0.0,-SQRT3/6.0),
            glm::vec3(0.0,0.0,SQRT3/3.0),
            glm::vec3(0.0,2*SQRT6/6.0,0),
            glm::vec3(0.0,-2*SQRT6/6.0,0),
    };

    unsigned int indices[] = {
            0,1,3,
            1,2,3,
            2,1,3,
            4,1,0,
            4,2,1,
            4,2,0,
    };

    for(int i=0;i<6;i++){
        glm::vec3 vec = calcNormal(verticesNormal[indices[i*3+0]],verticesNormal[indices[i*3+1]],verticesNormal[indices[i*3+2]]);
        std::cout << "t" << i << ": " << vec.x << ", " << vec.y << ", " << vec.z << "," << std::endl;
    }
    
}