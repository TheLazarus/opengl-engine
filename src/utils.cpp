#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <iostream>

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

// FrameBuffer Callback Used to resize Viewport

void frameBufferSizeCb(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int init(GLFWwindow **window, int majorVersion, int minorVersion)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    *window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);

    if (*window == NULL)
    {
        std::cout << "Failed to create the GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}