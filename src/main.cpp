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

int winWidth{1920}, winHeight{1080};

void frameBufferResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    winWidth = width;
    winHeight = height;
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
    GLFWwindow *window = glfwCreateWindow(winWidth, winHeight, "OpenGL Stuff", nullptr, nullptr);

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

            -0.5f,
            -0.5f,
            -1.5f,

            1.0f,
            0.0f,
            0.0f,

            0.5f,
            -0.5f,
            -1.5f,

            0.0f,
            1.0f,
            0.0f,

            0.0f,
            0.5f,
            -1.5f,

            0.0f,
            0.0f,
            1.0f,

        };

    // Index Array for using with EBOs
    unsigned int indices[] = {
        0, 1, 2};

    // Create a new VAO
    VAO vao;

    // Bind the VAO
    vao.bind();

    // Create a new VBO
    VBO vbo(vertexData, 18 * sizeof(float));

    // Bind the VBO
    vbo.bind();

    // Add attributes in VAO using the currently bound VBO
    vao.linkAttribute(vbo, 0, 3, (6 * sizeof(float)), (void *)(0));
    vao.linkAttribute(vbo, 1, 3, (6 * sizeof(float)), (void *)(3 * sizeof(float)));

    // Make a new EBO
    EBO ebo(indices, 3 * sizeof(unsigned int));

    // Unbind VAO and EBO
    vao.unbind();
    ebo.unbind();

    // Add vertex and fragment shaders
    ShaderProgram shaderProgram("./shaders/vertexShader.glsl", "./shaders/fragmentShader.glsl");

    // Render Loop
    while (!glfwWindowShouldClose(window))

    {

        // Clear Framebuffer image
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // Bind VAO and set the shader program to use
        vao.bind();
        shaderProgram.use();

        textureWindow.bind();

        // Perspective Projection Matrix
        glm::mat4 perspectiveMatrix = glm::perspective(glm::radians(45.0f), (float)(winWidth) / (float)(winHeight), 0.1f, 10.0f);

        // Rotation Matrix
        glm::mat4 model{1.0f};
        glm::mat4 rotationMatrix = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        // Setting Perspective Uniform
        int u_perspectiveLocation = glGetUniformLocation(shaderProgram.id, "u_perspective");
        glUniformMatrix4fv(u_perspectiveLocation, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));

        // Setting Rotation Uniform
        int u_rotationLocation = glGetUniformLocation(shaderProgram.id, "u_rotation");
        glUniformMatrix4fv(u_rotationLocation, 1, GL_FALSE, glm::value_ptr(rotationMatrix));

        // Setting Active Texture Unit Uniform
        int u_textureSamplerLocation = glGetUniformLocation(shaderProgram.id, "u_tex");
        glUniform1i(u_textureSamplerLocation, 0);

        // Pick indices from the EBO, and start drawing triangle primitives out from it.
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll Events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
