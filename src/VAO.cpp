#include "VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

void VAO::linkAttribute(VBO &vbo, unsigned int attributeIndex)
{
    vbo.bind();
    glVertexAttribPointer(attributeIndex, 3, GL_FLOAT, GL_FALSE, 0, (void *)(0));
    glEnableVertexAttribArray(attributeIndex);
    vbo.unbind();
}

void VAO::bind() const
{
    glBindVertexArray(id);
}

void VAO::unbind() const
{
    glBindVertexArray(0);
}

void VAO::del() const
{
    glDeleteVertexArrays(1, &id);
}