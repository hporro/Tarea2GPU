//
// Created by heini on 19-09-2019.
//

#ifndef TAREA2_SPHERE_H
#define TAREA2_SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "../Model.h"

/*
 * This idea of a sphere model derived from simpler ones comes from https://stackoverflow.com/a/7687312
 * Credits to the corresponding author.
 * */

namespace SPHERE {
    float StartingVertices[] = {
            -0.5,0.0,-SQRT3/6.0,
            0.5,0.0,-SQRT3/6.0,
            0.0,2*SQRT6/6.0,0,

            0.5,0.0,-SQRT3/6.0,
            0.0,0.0,SQRT3/3.0,
            0.0,2*SQRT6/6.0,0,

            0.0,0.0,SQRT3/3.0,
            -0.5,0.0,-SQRT3/6.0,
            0.0,2*SQRT6/6.0,0,

            0.0,-2*SQRT6/6.0,0,
            0.5,0.0,-SQRT3/6.0,
            -0.5,0.0,-SQRT3/6.0,

            0.0,-2*SQRT6/6.0,0,
            0.0,0.0,SQRT3/3.0,
            0.5,0.0,-SQRT3/6.0,

            -0.5,0.0,-SQRT3/6.0,
            0.0,0.0,SQRT3/3.0,
            0.0,-2*SQRT6/6.0,0,
    };

    glm::vec3 calcNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c){
        return glm::normalize(glm::cross((b-a),(c-a)));
    }

    struct Triangle {
        glm::vec3 a,b,c;
        Triangle(glm::vec3 a,glm::vec3 b,glm::vec3 c) : a(a),b(b),c(c){}
        Triangle(){}
    };

    template<class T>
    std::vector<T> concat(std::vector<T> v1, std::vector<T> v2){
        std::vector<T> res = std::vector<T>();
        res.insert(res.end(), v1.begin(), v1.end());
        res.insert(res.end(), v2.begin(), v2.end());
        return res;
    }

    std::vector<Triangle> divideTriangle(Triangle t){
        glm::vec3 a=t.a,b=t.b,c=t.c;
        glm::vec3 ac = (a+c)/(float)2.0;
        glm::vec3 ab = (a+b)/(float)2.0;
        glm::vec3 bc = (b+c)/(float)2.0;

        Triangle t1(a,ab,ac),
                 t2(ab,b,bc),
                 t3(ac,bc,c),
                 t4(ac,ab,bc);

        return std::vector<Triangle>({t1,t2,t3,t4});
    }

    Triangle normTriangle(Triangle t, glm::vec3 center, float rad){
        Triangle nt;
        //normalize the distance from the center of the sphere to each vertex of the triangle
        nt.a = center + (center-t.a)*rad/glm::distance(center,t.a);
        nt.b = center + (center-t.b)*rad/glm::distance(center,t.b);
        nt.c = center + (center-t.c)*rad/glm::distance(center,t.c);

        return nt;
    }

    std::vector<float> genVertices(int subdivitions, glm::vec3 center, float rad){
        std::vector<Triangle> finTriangles = std::vector<Triangle>();
        for(int i=0;i<6;i++){
            glm::vec3 a = glm::vec3(StartingVertices[i*9+0],StartingVertices[i*9+1],StartingVertices[i*9+2]);
            glm::vec3 b = glm::vec3(StartingVertices[i*9+3],StartingVertices[i*9+4],StartingVertices[i*9+5]);
            glm::vec3 c = glm::vec3(StartingVertices[i*9+6],StartingVertices[i*9+7],StartingVertices[i*9+8]);

            Triangle t0(a,b,c);
            std::vector<Triangle> triangles = std::vector<Triangle>({t0});

            for(int count=0;count<subdivitions;count++){
                std::vector<Triangle> aux = std::vector<Triangle>();
                for(Triangle t : triangles){
                    aux = concat(aux,divideTriangle(t));
                }
                triangles = aux;
            }

            finTriangles = concat(finTriangles,triangles);
        }

        std::vector<float> res = std::vector<float>();

        for(Triangle t0: finTriangles){

            Triangle t = normTriangle(t0,center,rad);
            glm::vec3 n = calcNormal(t.a,t.b,t.c);

            res.push_back(t.a.x);
            res.push_back(t.a.y);
            res.push_back(t.a.z);
            res.push_back(n.x);
            res.push_back(n.y);
            res.push_back(n.z);

            res.push_back(t.b.x);
            res.push_back(t.b.y);
            res.push_back(t.b.z);
            res.push_back(n.x);
            res.push_back(n.y);
            res.push_back(n.z);

            res.push_back(t.c.x);
            res.push_back(t.c.y);
            res.push_back(t.c.z);
            res.push_back(n.x);
            res.push_back(n.y);
            res.push_back(n.z);
        }

        return res;
    }
}

class Sphere : public Model {
public:
    Sphere(glm::vec3 position);
    void draw(glm::mat4 viewTransform, glm::mat4 projectionTransform);

private:
    std::vector<float> vertices;
};

Sphere::Sphere(glm::vec3 position) {

    vertices = SPHERE::genVertices(5,glm::vec3(0.0,0.0,0.0),1.0);

    modelTransform = glm::mat4(1.0f);
    modelTransform = glm::translate(modelTransform, position);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    /*std::cout << (vertices.size()/6) << std::endl;

    for(int i=0;i<vertices.size()/6;i++){
        std::cout << vertices[i*6+0] << " " << vertices[i*6+1] << " " << vertices[i*6+2] << " " << vertices[i*6+3] << " " << vertices[i*6+4] << " " << vertices[i*6+5] << std::endl;
    }*/
}

void Sphere::draw(glm::mat4 viewTransform, glm::mat4 projectionTransform) {
    shader.setMat4("model", modelTransform);
    shader.setMat4("view", viewTransform);
    shader.setMat4("projection", projectionTransform);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/6);
}

#endif //TAREA2_SPHERE_H
