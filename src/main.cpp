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

#define UNUSED(exp) (void)exp;

// Globals
unsigned int WIN_WIDTH{1920}, WIN_HEIGHT{1080};

float translateX{}, translateY{}, translateZ{};

const float X_ROTATION_SENS{0.5f}, Y_ROTATION_SENS{0.5f}, Z_ROTATION_SENS{0.5f};

// Frame Buffer Resize Callback
void frameBufferResizeCallback(GLFWwindow *window, int width, int height)
{
    UNUSED(window);
    glViewport(0, 0, width, height);
    WIN_WIDTH = width;
    WIN_HEIGHT = height;
}

// Key Press Callbacks
void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    UNUSED(window);
    UNUSED(scancode);
    UNUSED(action);
    UNUSED(mods);
    switch (key)
    {
    case GLFW_KEY_D:
        translateX += X_ROTATION_SENS;
        std::cout << "Current X Offset: " << translateX << std::endl;
        break;

    case GLFW_KEY_A:
        translateX -= X_ROTATION_SENS;
        std::cout << "Current X Offset: " << translateX << std::endl;
        break;
    case GLFW_KEY_W:
        translateY += Y_ROTATION_SENS;
        std::cout << "Current Y Offset: " << translateY << std::endl;
        break;
    case GLFW_KEY_S:
        translateY -= Y_ROTATION_SENS;
        std::cout << "Current Y Offset: " << translateY << std::endl;
        break;
    case GLFW_KEY_J:

        translateZ -= Z_ROTATION_SENS;
        std::cout << "Current Z Offset: " << translateZ << std::endl;
        break;
    case GLFW_KEY_K:
        translateZ += Z_ROTATION_SENS;
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

    // Enable Depth Testing, this prevents writes to framebuffer when the z values are greater than the existing values in the depth buffer
    glEnable(GL_DEPTH_TEST);

    // Set Window Resize Support
    glfwSetFramebufferSizeCallback(window, &frameBufferResizeCallback);

    // Listen for Keyboard Key Presses
    glfwSetKeyCallback(window, &keyCallback);

    float vertices[] = {

        -0.2f,
        -0.2f,
        -0.2f,

        1.0f,
        0.0f,
        0.0f,

        -0.2f,
        0.2f,
        -0.2f,

        0.0f,
        1.0f,
        0.5f,

        0.2f,
        0.2f,
        -0.2f,

        0.0f,
        0.0f,
        1.0f,

        0.2f,
        -0.2f,
        -0.2f,

        1.0f,
        0.0f,
        0.0f,

        -0.2f,
        -0.2f,
        0.2f,

        0.0f,
        1.0f,
        0.0f,

        -0.2f,
        0.2f,
        0.2f,

        0.0f,
        0.0f,
        1.0f,

        0.2f,
        0.2f,
        0.2f,

        1.0f,
        0.25f,
        0.0f,

        0.2f,
        -0.2f,
        0.2f,

        0.0f,
        1.0f,
        0.5f,

    };

    // Index Array for using with EBOs
    unsigned int indices[] = {
        0,
        1,
        2,

        2,
        3,
        0,

        4,
        5,
        6,

        6,
        4,
        7,

        0,
        1,
        5,

        5,
        4,
        0,

        3,
        2,
        6,

        6,
        7,
        3,

        1,
        2,
        5,

        5,
        6,
        2,

        0,
        4,
        3,

        3,
        7,
        4

    };

    // Create a new VAO
    VAO vao;

    // Bind the VAO
    vao.bind();

    // Create a new VBO
    VBO vbo(vertices, 48 * sizeof(float));

    // Bind the VBO
    vbo.bind();

    // Add attributes in VAO using the currently bound VBO
    vao.linkAttribute(vbo, 0, 3, 6 * sizeof(float), (void *)(0));
    vao.linkAttribute(vbo, 1, 3, 6 * sizeof(float), (void *)(3 * sizeof(float)));

    // Create and Bind the EBO

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

        for (size_t i = 0; i < 3; i++)
        {
            // Setting Up the Model Matrix
            glm::mat4 model(1.0f);
            model = glm::rotate(model, glm::radians(translateY), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(translateX), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(translateZ), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, -(float)(i)));
            int u_modelMatUniformLoc = glGetUniformLocation(shaderProgram.id, "u_model");
            glUniformMatrix4fv(u_modelMatUniformLoc, 1, GL_FALSE, glm::value_ptr(model));

            // Setting up the view matrix
            glm::mat4 view;
            view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f),
                               glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));

            int u_viewMatUniformLoc = glGetUniformLocation(shaderProgram.id, "u_view");
            glUniformMatrix4fv(u_viewMatUniformLoc, 1, GL_FALSE, glm::value_ptr(view));

            // Setting up the projection matrix
            glm::mat4 projection;
            projection = glm::perspective(glm::radians(45.0f), (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1f, 100.0f);
            int u_projectionMatUniformLoc = glGetUniformLocation(shaderProgram.id, "u_projection");
            glUniformMatrix4fv(u_projectionMatUniformLoc, 1, GL_FALSE, glm::value_ptr(projection));

            // Pick indices from the EBO, and start drawing triangle primitives out from it.
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll Events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
