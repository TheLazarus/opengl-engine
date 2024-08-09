#include "VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &id);
}

void VAO::linkAttribute(VBO &vbo, unsigned int attributeIndex, unsigned int noOfComponents, unsigned int stride, const void *offset)
{
    vbo.bind();
    glVertexAttribPointer(attributeIndex, noOfComponents, GL_FLOAT, GL_FALSE, stride, offset);
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