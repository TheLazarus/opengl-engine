#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>

class EBO
{

public:
    unsigned int id;

public:
    EBO(unsigned int *indices, unsigned int size);

    void bind() const;

    void unbind() const;

    void del() const;
};

#endif