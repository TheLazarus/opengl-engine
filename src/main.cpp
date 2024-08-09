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

            // Vertex 1
            -0.5f,
            0.0f,
            0.0f,

            0.55f,
            0.10f,
            0.90f,

            // Vertex 2
            -0.5f,
            0.5f,
            0.0f,

            0.15f,
            0.10f,
            0.70f,

            // Vertex 3
            0.0f,
            0.5f,
            0.0f,

            0.25f,
            0.25f,
            0.29f,

            // Vertex 4
            0.0f,
            0.0f,
            0.0f,

            0.55f,
            0.55f,
            0.10f,

            // Vertex 5
            0.0f,
            0.2f,
            0.0f,

            0.65f,
            0.65f,
            0.60f,

            // Vertex 6

            0.2f,
            0.2f,
            0.0f,

            0.65f,
            0.65f,
            0.60f,

            // Vertex 7

            0.2f,
            0.0f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            // Vertex 8

            0.4f,
            0.0f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            // Vertex 9

            0.4f,
            -0.25f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            // Vertex 10

            0.0f,
            -0.25f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            // Vertex 11

            0.0f,
            -0.5f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            // Vertex 12

            -0.5f,
            -0.5f,
            0.0f,

            0.05f,
            0.95f,
            0.40f,

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
    VBO vbo(vertexData, 72 * sizeof(float));

    vao.linkAttribute(vbo, 0, 3, 6 * sizeof(float), (void *)(0));
    vao.linkAttribute(vbo, 1, 3, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    EBO ebo(indices, 24 * sizeof(unsigned int));

    vao.unbind();
    ebo.unbind();

    Shader shader("./shaders/vertexShaderWithColors.glsl", "./shaders/fragmentShaderWithColors.glsl");

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
