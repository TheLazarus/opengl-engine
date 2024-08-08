#include <iostream>
#include "Shader.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include <GLFW/glfw3.h>

void frameBufferResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{

    if (glfwInit() == GLFW_FALSE)
    {
        std::cout << "ERROR :: Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "OpenGL Stuff", nullptr, nullptr);

    if (window == NULL)
    {
        std::cout << "ERROR :: Failed to create window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR :: Failed to initialize GLAD " << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);

    float vertexData[] =
        {
            -0.5f,
            0.0f,
            0.0f,

            -0.5f,
            0.5f,
            0.0f,

            0.0f,
            0.5f,
            0.0f,

            0.0f,
            0.0f,
            0.0f,

            0.0f,
            0.2f,
            0.0f,

            0.2f,
            0.2f,
            0.0f,

            0.2f,
            0.0f,
            0.0f,

            0.4f,
            0.0f,
            0.0f,

            0.4f,
            -0.25f,
            0.0f,

            0.0f,
            -0.25f,
            0.0f,

            0.0f,
            -0.5f,
            0.0f,

            -0.5f,
            -0.5f,
            0.0f,

        };

    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3,

        3, 4, 6,
        4, 5, 6,

        3, 7, 8,
        3, 8, 9,

        3, 10, 0,
        0, 10, 11

    };

    VAO vao;
    vao.bind();
    VBO vbo(vertexData, 36 * sizeof(float));

    vao.linkAttribute(vbo, 0);
    EBO ebo(indices, 24 * sizeof(unsigned int));

    vao.unbind();
    ebo.unbind();

    Shader shader("./shaders/vertexShader.glsl", "./shaders/fragmentShader.glsl");

    while (!glfwWindowShouldClose(window))
    {
        vao.bind();
        shader.use();

        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
