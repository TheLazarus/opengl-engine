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

    const float vertices[] = {
        // First Triangle's Vertex Data
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

    const float vertices_two[] = {
        // Second Triangle's Vertex Data
        0.8f,
        -0.5f,
        0.0f,

        0.9f,
        -0.5f,
        0.0f,

        0.85f,
        0.65f,
        0.0f};

    // Making a VAO
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vao2;
    glGenVertexArrays(1, &vao2);

    // Making a VBO
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // For Second Triangle
    glBindVertexArray(vao2);

    unsigned int vbo2;
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);

    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices_two, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

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

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(vao2);
        glDrawArrays(GL_LINE_STRIP, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}