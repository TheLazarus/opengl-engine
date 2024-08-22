#include <iostream>
#include "ShaderProgram.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "PerspectiveMatrix.hpp"
#include "TranslationMatrix.hpp"
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

// Globals
int WIN_WIDTH{1920}, WIN_HEIGHT{1080};

double translateX{}, translateY{}, translateZ{};

const double X_TRANSLATION_SENS{0.01}, Y_TRANSLATION_SENS{0.01}, Z_TRANSLATION_SENS{0.01};

// Frame Buffer Resize Callback
void frameBufferResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    WIN_WIDTH = width;
    WIN_HEIGHT = height;
}

// Key Press Callbacks
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_D:
        translateX += X_TRANSLATION_SENS;
        std::cout << "Current X Offset: " << translateX << std::endl;
        break;

    case GLFW_KEY_A:
        translateX -= X_TRANSLATION_SENS;
        std::cout << "Current X Offset: " << translateX << std::endl;
        break;
    case GLFW_KEY_W:
        translateY += Y_TRANSLATION_SENS;
        std::cout << "Current Y Offset: " << translateY << std::endl;
        break;
    case GLFW_KEY_S:
        translateY -= Y_TRANSLATION_SENS;
        std::cout << "Current Y Offset: " << translateY << std::endl;
        break;
    case GLFW_KEY_J:

        translateZ -= Z_TRANSLATION_SENS;
        std::cout << "Current Z Offset: " << translateZ << std::endl;
        break;
    case GLFW_KEY_K:
        translateZ += Z_TRANSLATION_SENS;
        std::cout << "Current Z Offset: " << translateZ << std::endl;
        break;
    }
}

// OpenGL Hints
void setOpenGLHints(unsigned int majorVersion, unsigned int minorVersion, unsigned int profile)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

// Entry
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
    GLFWwindow *window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "OpenGL Stuff", nullptr, nullptr);

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
    glfwSetFramebufferSizeCallback(window, &frameBufferResizeCallback);

    // Listen for Keyboard Key Presses
    glfwSetKeyCallback(window, &keyCallback);

    float vertexData[] =
        {

            -0.5f,
            -0.5f,
            0.0f,

            0.5f,
            -0.5f,
            0.0f,

            0.0f,
            0.5f,
            0.0f,

        };

    // Index Array for using with EBOs
    unsigned int indices[] = {
        0,
        1,
        2,

    };

    // Create a new VAO
    VAO vao;

    // Bind the VAO
    vao.bind();

    // Create a new VBO
    VBO vbo(vertexData, 9 * sizeof(float));

    // Bind the VBO
    vbo.bind();

    // Add attributes in VAO using the currently bound VBO
    vao.linkAttribute(vbo, 0, 3, 0, (void *)(0));

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

        // Setting Up Translation Matrix Uniform
        TranslationMatrix translationMatrix(translateX, translateY, translateZ);
        int u_translationMatrixLocation = glGetUniformLocation(shaderProgram.id, "u_translation");
        glUniformMatrix4fv(u_translationMatrixLocation, 1, GL_FALSE, &translationMatrix);

        // Setting Up Perspective Projection Uniform
        PerspectiveMatrix perspectiveMatrix(0.1f, 0.35f, -0.4f, 0.4f, 0.4f, -0.4f);
        int u_perspectiveMatrixLocation = glGetUniformLocation(shaderProgram.id, "u_perspective");
        glUniformMatrix4fv(u_perspectiveMatrixLocation, 1, GL_FALSE, &perspectiveMatrix);

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
