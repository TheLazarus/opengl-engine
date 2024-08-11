#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <fstream>

class ShaderProgram
{
public:
    unsigned int m_programId;

public:
    ShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);

    void use();
};

#endif