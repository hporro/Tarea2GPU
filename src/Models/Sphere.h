#ifndef TAREA2_SPHERE_H
#define TAREA2_SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "../Model.h"

/*
 * This idea of a sphere model derived from a cubical one comes from https://stackoverflow.com/a/7687312
 * Credits to the corresponding author.
 * */

namespace SPHERE {
    float StartingVertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    glm::vec3 calcNormal(glm::vec3 center,glm::vec3 a, glm::vec3 b, glm::vec3 c){
        return glm::normalize(glm::cross((b-a),(c-a)));
    }

    struct Triangle {
        glm::vec3 a,b,c;
        glm::vec2 auv,buv,cuv;
        Triangle(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec2 auv,glm::vec2 buv,glm::vec2 cuv) : a(a),b(b),c(c),auv(auv),buv(buv),cuv(cuv){}
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
        glm::vec2 auv = t.auv, buv = t.buv, cuv = t.cuv;
        glm::vec2 acuv = (auv+cuv)/(float)2.0;
        glm::vec2 abuv = (auv+buv)/(float)2.0;
        glm::vec2 bcuv = (buv+cuv)/(float)2.0;


        Triangle t1(a,ab,ac,auv,abuv,acuv),
                 t2(ab,b,bc,abuv,buv,bcuv),
                 t3(ac,bc,c,acuv,bcuv,cuv),
                 t4(ac,ab,bc,acuv,abuv,bcuv);

        return std::vector<Triangle>({t1,t2,t3,t4});
    }

    Triangle normTriangle(Triangle t, glm::vec3 center, float rad){
        Triangle nt;
        //normalize the distance from the center of the sphere to each vertex of the triangle
        nt.a = center + (center-t.a)*rad/glm::distance(center,t.a);
        nt.b = center + (center-t.b)*rad/glm::distance(center,t.b);
        nt.c = center + (center-t.c)*rad/glm::distance(center,t.c);
        nt.auv = t.auv;
        nt.buv = t.buv;
        nt.cuv = t.cuv;

        return nt;
    }

    std::vector<float> genVertices(int subdivitions, glm::vec3 center, float rad){
        std::vector<Triangle> finTriangles = std::vector<Triangle>();
        for(int i=0;i<12;i++){
            glm::vec3 a = glm::vec3(StartingVertices[i*24+0],StartingVertices[i*24+1],StartingVertices[i*24+2]);
            glm::vec3 b = glm::vec3(StartingVertices[i*24+8],StartingVertices[i*24+9],StartingVertices[i*24+10]);
            glm::vec3 c = glm::vec3(StartingVertices[i*24+16],StartingVertices[i*24+17],StartingVertices[i*24+18]);

            glm::vec2 auv = glm::vec2(StartingVertices[i*24+6],StartingVertices[i*24+7]);
            glm::vec2 buv = glm::vec2(StartingVertices[i*24+14],StartingVertices[i*24+15]);
            glm::vec2 cuv = glm::vec2(StartingVertices[i*24+22],StartingVertices[i*24+23]);


            Triangle t0(a,b,c,auv,buv,cuv);
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
            glm::vec3 n = calcNormal(center,t.a,t.b,t.c);

            res.push_back(t.a.x);
            res.push_back(t.a.y);
            res.push_back(t.a.z);
            res.push_back(n.x);
            res.push_back(n.y);
            res.push_back(n.z);
            res.push_back(t.auv.x);
            res.push_back(t.auv.y);


            res.push_back(t.b.x);
            res.push_back(t.b.y);
            res.push_back(t.b.z);
            res.push_back(n.x);
            res.push_back(n.y);
            res.push_back(n.z);
            res.push_back(t.buv.x);
            res.push_back(t.buv.y);

            res.push_back(t.c.x);
            res.push_back(t.c.y);
            res.push_back(t.c.z);
            res.push_back(n.x);
            res.push_back(n.y);
            res.push_back(n.z);
            res.push_back(t.cuv.x);
            res.push_back(t.cuv.y);
        }

        return res;
    }
}

class Sphere : public Model {
public:
    Sphere(){};
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}

void Sphere::draw(glm::mat4 viewTransform, glm::mat4 projectionTransform) {
    shader.setMat4("model", modelTransform);
    shader.setMat4("view", viewTransform);
    shader.setMat4("projection", projectionTransform);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/8);
}

#endif //TAREA2_SPHERE_H
