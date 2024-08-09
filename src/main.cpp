#include <iostream>
#include "Shader.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include <GLFW/glfw3.h>
#include <stb_image.h>

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

    unsigned int texture{};
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    // Texture Parameter Settings

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Loading Images via STB

    int width{}, height{}, channels{};

    unsigned char *data = stbi_load("./textures/ezio.jpg", &width, &height, &channels, 0);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    else
    {
        std::cout << "ERROR :: Failed to Load Texture" << std::endl;
    }

    stbi_image_free(data);

    float vertexData[] =
        {

            // Vertex 1
            // V1 Position
            -0.5f,
            0.0f,
            0.0f,

            // V1 Color
            0.55f,
            0.10f,
            0.90f,

            // Texture Coordinates
            0.65f,
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
            0.0f,
            0.5f,
            0.0f,

            0.25f,
            0.25f,
            0.29f,

            1.0f,
            1.0f,

            // Vertex 4
            0.0f,
            0.0f,
            0.0f,

            0.55f,
            0.55f,
            0.10f,

            1.0f,
            0.0f,

            // Vertex 5
            0.0f,
            0.2f,
            0.0f,

            0.65f,
            0.65f,
            0.60f,

            0.65f,
            0.35f,

            // Vertex 6

            0.2f,
            0.2f,
            0.0f,

            0.65f,
            0.65f,
            0.60f,

            0.65f,
            0.77f,

            // Vertex 7

            0.2f,
            0.0f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            0.77f,
            0.65f,

            // Vertex 8

            0.4f,
            0.0f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            0.77f,
            0.10f,

            // Vertex 9

            0.4f,
            -0.25f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            0.0f,
            0.0f,

            // Vertex 10

            0.0f,
            -0.25f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            0.0f,
            0.0f,

            // Vertex 11

            0.0f,
            -0.5f,
            0.0f,

            0.15f,
            0.15f,
            0.10f,

            0.0f,
            0.0f,

            // Vertex 12

            -0.5f,
            -0.5f,
            0.0f,

            0.05f,
            0.95f,
            0.40f,

            0.0f,
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
    VBO vbo(vertexData, 96 * sizeof(float));

    vao.linkAttribute(vbo, 0, 3, 8 * sizeof(float), (void *)(0));
    vao.linkAttribute(vbo, 1, 3, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    vao.linkAttribute(vbo, 2, 2, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    EBO ebo(indices, 24 * sizeof(unsigned int));

    vao.unbind();
    ebo.unbind();

    Shader shader("./shaders/vertexShaderWithColors.glsl", "./shaders/fragmentShaderWithColors.glsl");

    while (!glfwWindowShouldClose(window))
    {
        glBindTexture(GL_TEXTURE_2D, texture);
        vao.bind();
        shader.use();

        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
