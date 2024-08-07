#include <iostream>
#include "classes/Shader.hpp"
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

    const float triangleVertices[] = {
        -0.5f,
        -0.5f,
        0.0f,

        0.25f,
        0.50f,
        0.70f,

        0.0f,
        0.5f,
        0.0f,

        0.45f,
        0.10f,
        0.80f,

        0.5f,
        -0.5f,
        0.0f,

        0.15f,
        0.05f,
        0.40f,

    };

    const float secondTriangleVertices[] = {
        0.0f,
        0.0f,
        0.0f,
        0.5f,
        0.5f,
        0.0f,
        0.25f,
        -0.5f,
        0.0f};

    // Creating VAOs for Meshes
    unsigned int triangleVAO{};
    glGenVertexArrays(1, &triangleVAO);

    unsigned int secondTriangleVAO{};
    glGenVertexArrays(1, &secondTriangleVAO);

    // Binding the first VAO here
    glBindVertexArray(triangleVAO);

    // VBO for rendering first triangle
    unsigned int triangleVBO{};
    glGenBuffers(1, &triangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);

    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), (void *)triangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(0));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Binding Second VAO here
    glBindVertexArray(secondTriangleVAO);

    // Making another VBO for the second triangle
    unsigned int secondTriangleVBO{};
    glGenBuffers(1, &secondTriangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, secondTriangleVBO);

    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), (void *)secondTriangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)(0));

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    Shader shader("./shaders/vertexShader.glsl", "./shaders/fragmentShader.glsl");
    Shader shaderWithColors("./shaders/vertexShaderWithColors.glsl", "./shaders/fragmentShaderWithColors.glsl");

    while (!glfwWindowShouldClose(window))
    {
        shaderWithColors.use();
        glBindVertexArray(triangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        shader.use();
        glBindVertexArray(secondTriangleVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
