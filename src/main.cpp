#include <iostream>
#include <fstream>
#include <sstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <app/main.h>
#include <app/utils.h>

int main()
{

    GLFWwindow *window = nullptr;

    if (init(&window, 3, 3) == -1)
    {
        std::cout << "Some error occured while initializing GLFW!" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD " << "\n";
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, frameBufferSizeCb);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.2f, -0.4f, 0.0f,
        0.1f, -0.1f, 0.0f,
        0.8f, -0.9f, 0.0f};

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);

    unsigned int pointsBuffer;
    glGenBuffers(1, &pointsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        glDrawArrays(GL_POINTS, 0, 6);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
