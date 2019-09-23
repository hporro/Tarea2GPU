//
// Created by heini on 13-09-2019.
//

#ifndef LEARNOPENGL_TEXTURE_H
#define LEARNOPENGL_TEXTURE_H

#include "../../libs/stb_image.h"

#include <glad/glad.h>
#include <iostream>

class Texture{
public:
    Texture(const char *textureLocation, bool setFlip, unsigned int dataType);
    Texture() = default;

    void bind(int i);
private:
    unsigned int texture;
    int width, height, nrChannels;
};

Texture::Texture(const char *textureLocation, bool setFlip, unsigned int dataType) {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    stbi_set_flip_vertically_on_load(setFlip);
    unsigned char *data = stbi_load(textureLocation, &width, &height, &nrChannels, 0);
    if (data){
        //hace la textura y genera mipmaps
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, dataType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

void Texture::bind(int gl_textureNumber) {
    glActiveTexture(gl_textureNumber);
    glBindTexture(GL_TEXTURE_2D, texture);
}

#endif //LEARNOPENGL_TEXTURE_H
