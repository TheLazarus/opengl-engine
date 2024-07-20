#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <app/app>
#include <iostream>

int main()
{

    GLFWwindow *window = nullptr;
    if (init(window) == -1)
    {
        std::cout << "Some error occured while initializing GLFW!" << std::endl;
        return -1;
    }

    std::cout << window << std::endl;

        while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

int init(GLFWwindow *window)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "Triangles", NULL, NULL);

    if (!window)
    {
        std::cout << "Failed to create the GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    return 0;
}
