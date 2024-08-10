#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>

class Texture
{

public:
    unsigned int id;

public:
    Texture();

    void bind() const;

    void unbind() const;

    void del() const;

    int source(const char *texturePath) const;
};

#endif