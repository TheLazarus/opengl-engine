#include <iostream>
#include "Shader.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "Texture.hpp"
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    // Generating a texture object

    Texture textureWindow;
    // Texture Parameter Settings

    textureWindow.bind();
    textureWindow.source("./textures/window.jpg");

    // Texture Configurations

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    float vertexData[] =
        {

            // Vertex 1
            // V1 Position
            -0.5f,
            -0.5f,
            0.0f,

            // V1 Color
            0.55f,
            0.10f,
            0.90f,

            // Texture Coordinates
            0.0f,
            0.0f,

            // Vertex 2
            -0.5f,
            0.5f,
            0.0f,

            0.15f,
            0.10f,
            0.70f,

            0.0f,
            1.0f,

            // Vertex 3
            0.5f,
            0.5f,
            0.0f,

            0.25f,
            0.25f,
            0.29f,

            1.0f,
            1.0f,

            // Vertex 4
            0.5f,
            -0.5f,
            0.0f,

            0.55f,
            0.55f,
            0.10f,

            1.0f,
            0.0f,

            // // Vertex 5
            // 0.0f,
            // 0.2f,
            // 0.0f,

            // 0.65f,
            // 0.65f,
            // 0.60f,

            // 0.65f,
            // 0.35f,

            // // Vertex 6

            // 0.2f,
            // 0.2f,
            // 0.0f,

            // 0.65f,
            // 0.65f,
            // 0.60f,

            // 0.65f,
            // 0.77f,

            // // Vertex 7

            // 0.2f,
            // 0.0f,
            // 0.0f,

            // 0.15f,
            // 0.15f,
            // 0.10f,

            // 0.77f,
            // 0.65f,

            // // Vertex 8

            // 0.4f,
            // 0.0f,
            // 0.0f,

            // 0.15f,
            // 0.15f,
            // 0.10f,

            // 0.77f,
            // 0.10f,

            // // Vertex 9

            // 0.4f,
            // -0.25f,
            // 0.0f,

            // 0.15f,
            // 0.15f,
            // 0.10f,

            // 0.0f,
            // 0.0f,

            // // Vertex 10

            // 0.0f,
            // -0.25f,
            // 0.0f,

            // 0.15f,
            // 0.15f,
            // 0.10f,

            // 0.0f,
            // 0.0f,

            // // Vertex 11

            // 0.0f,
            // -0.5f,
            // 0.0f,

            // 0.15f,
            // 0.15f,
            // 0.10f,

            // 0.0f,
            // 0.0f,

            // // Vertex 12

            // -0.5f,
            // -0.5f,
            // 0.0f,

            // 0.05f,
            // 0.95f,
            // 0.40f,

            // 0.0f,
            // 0.0f,

        };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0};

    VAO vao;
    vao.bind();
    VBO vbo(vertexData, 32 * sizeof(float));

    vao.linkAttribute(vbo, 0, 3, 8 * sizeof(float), (void *)(0));
    vao.linkAttribute(vbo, 1, 3, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    vao.linkAttribute(vbo, 2, 2, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    EBO ebo(indices, 6 * sizeof(unsigned int));

    vao.unbind();
    ebo.unbind();

    Shader shader("./shaders/vertexShaderWithColors.glsl", "./shaders/fragmentShaderWithColors.glsl");

    while (!glfwWindowShouldClose(window))
    {

        vao.bind();
        shader.use();

        textureWindow.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
