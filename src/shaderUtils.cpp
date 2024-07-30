#include <glad/glad.h>
#include <fstream>
#include <sstream>

void readShader(std::string &shader, std::string shaderPath)
{
    std::ifstream vertexShaderSource(shaderPath);

    if (vertexShaderSource)
    {
        std::ostringstream ss;
        ss << vertexShaderSource.rdbuf();
        shader = ss.str();
    }
}

void printShaderInfoLog(unsigned int shaderIndex)
{
    int maxLength{2048};
    int actualLength{};
    char *shaderLog{};

    glGetShaderInfoLog(shaderIndex, maxLength, &actualLength, shaderLog);
}

void printProgramInfoLog(unsigned int programIndex)
{
    int maxLength{2048};
    int actualLength{};
    char *programLog{};

    glGetProgramInfoLog(programIndex, maxLength, &actualLength, programLog);
}