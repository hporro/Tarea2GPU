#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>

#include "tiny_obj_loader.h"

int main(){
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

    std::cout << shapes[0].mesh.num_face_vertices.size() << std::endl;
    for(int i=0;i<shapes[0].mesh.num_face_vertices.size();i++){
        if(shapes[0].mesh.num_face_vertices[i]>3)std::cout << "AAAAAAAAAAAAA" << std::endl;
    }

    /*for(int i=0;i<attrib.vertices.size()/3;i++){
        std::cout << "v: " << attrib.vertices[i*3+0] << " " << attrib.vertices[i*3+1] << " " << attrib.vertices[i*3+2] << std::endl;
        std::cout << "vn: " << attrib.normals[i*3+0] << " " << attrib.normals[i*3+1] << " " << attrib.normals[i*3+2] << std::endl;
    }*/
}