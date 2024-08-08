#ifndef VBO_H
#define VBO_H

#include <glad/glad.h>

class VBO
{
public:
    unsigned int id;

public:
    VBO(float *vertices, unsigned int size);

    void bind() const;

    void unbind() const;

    void del() const;
};

#endif