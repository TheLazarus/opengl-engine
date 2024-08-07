#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

void frameBufferSizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

int main()
{
    if (glfwInit() == 0)
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1920, 1080, "My First Triangle Baby!", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD " << "\n";
        glfwTerminate();
        return -1;
    }

    const float rectangleVertices[] = {
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,

        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f};

    // For rendering using Vertex Streams
    unsigned int rectangleVAO;
    glGenVertexArrays(1, &rectangleVAO);
    glBindVertexArray(rectangleVAO);

    unsigned int rectangleVBO;
    glGenBuffers(1, &rectangleVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectangleVBO);

    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), rectangleVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // For Rendering Using EBOs and Indices

    unsigned int indices[] = {0, 1, 2, 3, 4, 5};

    unsigned int ebo;
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Getting Vertex Shader Content
    std::ifstream vertexShaderFile;
    vertexShaderFile.open("./shaders/vertexShader.glsl");

    std::stringstream vertexShaderSStream;
    vertexShaderSStream << vertexShaderFile.rdbuf();
    std::string vertexShaderString = vertexShaderSStream.str();

    const char *vertexShaderSource = vertexShaderString.c_str();

    // Getting Fragment Shader Content
    std::ifstream fragmentShaderFile;
    fragmentShaderFile.open("./shaders/fragmentShader.glsl");

    std::stringstream fragmentShaderSStream;
    fragmentShaderSStream << fragmentShaderFile.rdbuf();
    std::string fragmentShaderString = fragmentShaderSStream.str();

    const char *fragmentShaderSource = fragmentShaderString.c_str();

    // Sourcing and Compiling Shaders
    unsigned int vertexShaderObj;
    vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexShaderObj, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShaderObj);

    unsigned int fragmentShaderObj;
    fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(fragmentShaderObj, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaderObj);

    // Making a Shader Program

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShaderObj);
    glAttachShader(shaderProgram, fragmentShaderObj);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShaderObj);
    glDeleteShader(fragmentShaderObj);

    while (!glfwWindowShouldClose(window))
    {
        glUseProgram(shaderProgram);

        glBindVertexArray(rectangleVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}