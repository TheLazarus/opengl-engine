#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>

class ShaderProgram
{
public:
    unsigned int id;

public:
    ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);

    void use();
};

#endif