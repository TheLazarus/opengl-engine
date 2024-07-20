#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static unsigned int compileShader(unsigned int type, const std::string &source)
{
    unsigned int shaderId = glCreateShader(type);
    const char *src = source.c_str();

    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);

    int result{};
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length{};
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)(alloca(length * sizeof(char)));
        glGetShaderInfoLog(shaderId, length, &length, message);

        std::string shaderType = type == GL_VERTEX_SHADER ? "Vertex" : "Fragment";

        std::cout << shaderType << " Shader Compilation Failed - " << message << "\n";
        glDeleteShader(shaderId);
        return 0;
    }

    return shaderId;
}

static int createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = glCreateProgram();

    unsigned int vertexShaderId = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragmentShaderId = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertexShaderId);
    glAttachShader(program, fragmentShaderId);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    return program;
}

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "GLFW Window", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW Window" << "\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD " << "\n";
        return -1;
    }

    glViewport(0, 0, 800, 600);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f};

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    std::string vertexShader =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}";

    std::string fragmentShader =
        "#version 330 core\n"
        "out vec4 FragColor;"
        "\n"
        "void main()\n"
        "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);"
        "}";

    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
