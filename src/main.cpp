#include <iostream>
#include "ShaderProgram.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

// Globals
int winWidth{2500}, winHeight{1080};

float translateX{}, translateY{}, translateZ{};

const float X_TRANSLATION_SENS{0.01f}, Y_TRANSLATION_SENS{0.01f}, Z_TRANSLATION_SENS{0.01f};

void frameBufferResizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    winWidth = width;
    winHeight = height;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_D:
        translateX += X_TRANSLATION_SENS;
        break;

    case GLFW_KEY_A:
        translateX -= X_TRANSLATION_SENS;
        break;
    case GLFW_KEY_W:
        translateY += Y_TRANSLATION_SENS;
        break;
    case GLFW_KEY_S:
        translateY -= Y_TRANSLATION_SENS;
        break;
    case GLFW_KEY_J:

        translateZ -= Z_TRANSLATION_SENS;
        std::cout << translateZ << std::endl;
        break;
    case GLFW_KEY_K:
        translateZ += Z_TRANSLATION_SENS;
        std::cout << translateZ << std::endl;
        break;
    }
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
    glfwSetFramebufferSizeCallback(window, &frameBufferResizeCallback);

    // Listen for Keyboard Key Presses
    glfwSetKeyCallback(window, &keyCallback);

    float vertexData[] =
        {

            0.5f,
            0.5f,
            0.5f,

            -0.5f,
            0.5f,
            -0.5f,

            -0.5f,
            0.5f,
            0.5f,

            0.5f,
            -0.5f,
            -0.5f,

            -0.5f,
            -0.5f,
            -0.5f,

            0.5f,
            0.5f,
            -0.5f,

            0.5f,
            -0.5f,
            0.5f,

            -0.5f,
            -0.5f,
            0.5f

        };

    // Index Array for using with EBOs
    unsigned int indices[] = {
        0, 1, 2,
        1, 3, 4,
        5, 6, 3,
        7, 3, 6,
        2, 4, 7,
        0, 7, 6,
        0, 5, 1,
        1, 5, 3,
        5, 0, 6,
        7, 4, 3,
        2, 1, 4,
        0, 2, 7

    };

    // Create a new VAO
    VAO vao;

    // Bind the VAO
    vao.bind();

    // Create a new VBO
    VBO vbo(vertexData, 24 * sizeof(float));

    // Bind the VBO
    vbo.bind();

    // Add attributes in VAO using the currently bound VBO
    vao.linkAttribute(vbo, 0, 3, 0, (void *)(0));

    // Make a new EBO
    EBO ebo(indices, 36 * sizeof(unsigned int));

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

        // Perspective Matrix
        float fov = 90.0f;
        float tanHalfFOV = 1 / glm::tan(glm::radians(fov / 2));
        float aspectRatio = (float)winWidth / (float)winHeight;
        glm::mat4 projectionMatrix{tanHalfFOV / aspectRatio, 0.0f, 0.0f, 0.0f, 0.0f, tanHalfFOV / aspectRatio, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f};

        // Translation Matrix
        glm::mat4 translationMatrix{1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, translateX, translateY, translateZ, 1.0f};

        // Setting Up Translation Matrix Uniform
        int u_translationMatrixLocation = glGetUniformLocation(shaderProgram.id, "u_translation");
        glUniformMatrix4fv(u_translationMatrixLocation, 1, GL_FALSE, glm::value_ptr(translationMatrix));

        // Setting Up Perspective Projection Uniform
        int u_perspectiveMatrixLocation = glGetUniformLocation(shaderProgram.id, "u_perspective");
        glUniformMatrix4fv(u_perspectiveMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

        // Pick indices from the EBO, and start drawing triangle primitives out from it.
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll Events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
