#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include "VBO.hpp"

class VAO
{
public:
    unsigned int id;

public:
    VAO();

    void linkAttribute(VBO &vbo, unsigned int attributeIndex);

    void bind() const;

    void unbind() const;

    void del() const;
};

#endif