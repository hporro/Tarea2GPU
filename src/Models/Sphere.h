//
// Created by heini on 19-09-2019.
//

#ifndef TAREA2_SPHERE_H
#define TAREA2_SPHERE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#include "../Figure.h"
#include "../Model.h"

namespace SPHERE {
#define SQRT3 1.7320508076
#define SQRT6 2.4494897428
#define EPS 0.0000001

    float StartingVertices[] = {
            -0.5,0.0,-SQRT3/6.0,-0, 0.333333, -0.942809,
            0.5,0.0,-SQRT3/6.0,-0, 0.333333, -0.942809,
            0.0,2*SQRT6/6.0,0,-0, 0.333333, -0.942809,

            0.5,0.0,-SQRT3/6.0,0.816497, 0.333333, 0.471405,
            0.0,0.0,SQRT3/3.0,0.816497, 0.333333, 0.471405,
            0.0,2*SQRT6/6.0,0,0.816497, 0.333333, 0.471405,

            0.0,0.0,SQRT3/3.0,-0.816497, -0.333333, -0.471405,
            -0.5,0.0,-SQRT3/6.0,-0.816497, -0.333333, -0.471405,
            0.0,2*SQRT6/6.0,0,-0.816497, -0.333333, -0.471405,

            0.0,-2*SQRT6/6.0,0,0, 0.333333, 0.942809,
            0.5,0.0,-SQRT3/6.0,0, 0.333333, 0.942809,
            -0.5,0.0,-SQRT3/6.0,0, 0.333333, 0.942809,

            0.0,-2*SQRT6/6.0,0,-0.816497, 0.333333, -0.471405,
            0.0,0.0,SQRT3/3.0,-0.816497, 0.333333, -0.471405,
            0.5,0.0,-SQRT3/6.0,-0.816497, 0.333333, -0.471405,

            0.0,-2*SQRT6/6.0,0,-0.816497, -0.333333, 0.471405,
            0.0,0.0,SQRT3/3.0,-0.816497, -0.333333, 0.471405,
            -0.5,0.0,-SQRT3/6.0,-0.816497, -0.333333, 0.471405,

            /*
            -0.5,0.0,-SQRT3/6.0,
            0.5,0.0,-SQRT3/6.0,
            0.0,0.0,SQRT3/3.0,
            0.0,2*SQRT6/6.0,0,
            0.0,-2*SQRT6/6.0,0,
             */
    };

    glm::vec3 calcNormal(glm::vec3 a, glm::vec3 b, glm::vec3 c){
        return -glm::normalize(glm::cross((b-a),(c-a)));
    }

    struct Triangle {
        glm::vec3 a,b,c;
        glm::vec3 n;
        Triangle(glm::vec3 a,glm::vec3 b,glm::vec3 c,glm::vec3 n) : a(a),b(b),c(c),n(n){}
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

        Triangle t1,t2,t3,t4;
        t1.a = a; t1.b = ab; t1.c = ac; t1.n = calcNormal(t1.a,t1.b,t1.c);
        t2.a = ab; t2.b = b; t2.c = bc; t2.n = calcNormal(t2.a,t2.b,t2.c);
        t3.a = ac; t3.b = bc; t3.c = c; t3.n = calcNormal(t3.a,t3.b,t3.c);
        t4.a = ac; t4.b = ab; t4.c = bc; t4.n = calcNormal(t4.a,t4.b,t4.c);

        return std::vector<Triangle>({t1,t2,t3,t4});
    }

    Triangle normTriangle(Triangle t, glm::vec3 center, float rad){
        /*
         function normalize(a, b, length):
            #get the distance between a and b along the x and y axes
            dx = b.x - a.x
            dy = b.y - a.y
            #right now, sqrt(dx^2 + dy^2) = distance(a,b).
            #we want to modify them so that sqrt(dx^2 + dy^2) = the given length.
            dx = dx * length / distance(a,b)
            dy = dy * length / distance(a,b)
            point c =  new point
            c.x = a.x + dx
            c.y = a.y + dy
            return c
        */

        Triangle nt;
        nt.a = t.a + (center-t.a)*rad/glm::distance(center,t.a);
        nt.b = t.b + (center-t.b)*rad/glm::distance(center,t.b);
        nt.c = t.c + (center-t.c)*rad/glm::distance(center,t.c);

        nt.n = calcNormal(nt.a,nt.b,nt.c);

        return nt;
    }

    std::vector<float> genVertices(int subdivitions, float rad, glm::vec3 center){
        std::vector<Triangle> finTriangles = std::vector<Triangle>();
        for(int i=0;i<6;i++){
            glm::vec3 a = glm::vec3(StartingVertices[i*18+0],StartingVertices[i*18+1],StartingVertices[i*18+2]);
            glm::vec3 b = glm::vec3(StartingVertices[i*18+6],StartingVertices[i*18+7],StartingVertices[i*18+8]);
            glm::vec3 c = glm::vec3(StartingVertices[i*18+12],StartingVertices[i*18+13],StartingVertices[i*18+14]);
            glm::vec3 n = glm::vec3(StartingVertices[i*18+3],StartingVertices[i*18+4],StartingVertices[i*18+5]);

            Triangle t0(a,b,c,n);
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

            res.push_back(t.a.x);
            res.push_back(t.a.y);
            res.push_back(t.a.z);
            res.push_back(t.n.x);
            res.push_back(t.n.y);
            res.push_back(t.n.z);

            res.push_back(t.b.x);
            res.push_back(t.b.y);
            res.push_back(t.b.z);
            res.push_back(t.n.x);
            res.push_back(t.n.y);
            res.push_back(t.n.z);

            res.push_back(t.c.x);
            res.push_back(t.c.y);
            res.push_back(t.c.z);
            res.push_back(t.n.x);
            res.push_back(t.n.y);
            res.push_back(t.n.z);
        }

        return res;
    }
}

class Sphere : public Model {
public:
    Sphere();
    Sphere(glm::vec3 position);
    void draw(glm::mat4 viewTransform, glm::mat4 projectionTransform);

private:
    std::vector<float> vertices;
};

Sphere::Sphere(glm::vec3 position) {

    vertices = SPHERE::genVertices(5,1.0,glm::vec3(0.0,0.0,0.0));

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

Sphere::Sphere(){
    Sphere(glm::vec3(0.0f,0.0f,0.0f));
}

void Sphere::draw(glm::mat4 viewTransform, glm::mat4 projectionTransform) {
    shader.setMat4("model", modelTransform);
    shader.setMat4("view", viewTransform);
    shader.setMat4("projection", projectionTransform);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size()/6);
}

#endif //TAREA2_SPHERE_H
