#include <iostream>
#include "ShaderProgram.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "Texture.hpp"
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>

void frameBufferResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void setOpenGLHints(unsigned int majorVersion, unsigned int minorVersion, unsigned int profile)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

int main()
{

    // Initialize GLFW
    if (glfwInit() == GLFW_FALSE)
    {
        std::cerr << "ERROR :: Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Set OpenGL Hints to request a particular version and profile.
    setOpenGLHints(3, 3, GLFW_OPENGL_CORE_PROFILE);

    // Create a new Window
    GLFWwindow *window = glfwCreateWindow(1920, 1080, "OpenGL Stuff", nullptr, nullptr);

    if (window == NULL)
    {
        std::cerr << "ERROR :: Failed to create window" << std::endl;
        return -1;
    }

    // Set current window to initialize a new OpenGL context
    glfwMakeContextCurrent(window);

    // Load function pointers from drivers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "ERROR :: Failed to initialize GLAD " << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set Window Resize Support
    glfwSetFramebufferSizeCallback(window, frameBufferResizeCallback);

    // Generating a texture object

    Texture textureWindow;
    // Texture Parameter Settings

    textureWindow.bind();
    textureWindow.source("./textures/window.jpg");

    // Texture Configurations

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    float vertexData[] =
        {

            0.0f,
            0.0f,
            0.0f,

            0.5f,
            0.10f,
            0.25f,

            0.5f,
            0.5f,
            0.0f,

            0.5f,
            0.10f,
            0.25f,

        };

    // Index Array for using with EBOs
    unsigned int indices[] = {
        0, 1};

    // Create a new VAO
    VAO vao;

    // Bind the VAO
    vao.bind();

    // Create a new VBO
    VBO vbo(vertexData, 12 * sizeof(float));

    // Bind the VBO
    vbo.bind();

    // Add attributes in VAO using the currently bound VBO
    vao.linkAttribute(vbo, 0, 3, 6 * sizeof(float), (void *)(0));
    vao.linkAttribute(vbo, 1, 3, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    // Make a new EBO
    EBO ebo(indices, 2 * sizeof(unsigned int));

    // Unbind VAO and EBO
    vao.unbind();
    ebo.unbind();

    // Add vertex and fragment shaders
    ShaderProgram shaderProgram("./shaders/vertexShaderWithColors.glsl", "./shaders/fragmentShaderWithColors.glsl");

    // Render Loop
    while (!glfwWindowShouldClose(window))
    {

        // Bind VAO and set the shader program to use
        vao.bind();
        shaderProgram.use();

        double elapsedTime = glfwGetTime();

        std::cout << "Elpased Time : " << elapsedTime << std::endl;

        int uniform_translationMatrix = glGetUniformLocation(shaderProgram.id, "translationMatrix");
        glm::mat4x4 translationMatrix(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, sin(elapsedTime) / 3.0f, sin(elapsedTime) / 5.0f, 0.0f, 1.0f);

        glUniformMatrix4fv(uniform_translationMatrix, 1, false, glm::value_ptr(translationMatrix));

        // Pick 6 elements from the EBO, and start drawing triangle primitives out from it.
        glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, 0);

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll Events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
