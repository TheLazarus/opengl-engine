#include <glad/glad.h>
#include <app/app>
#include <fstream>
#include <sstream>

int main()
{
    const std::string VERTEX_SHADER_PATH = "./shaders/vertexShader.shader";
    const std::string FRAGMENT_SHADER_PATH = "./shaders/fragmentShader.shader";

    GLFWwindow *window = nullptr;
    if (init(&window) == -1)
    {
        std::cout << "Some error occured while initializing GLFW!" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD " << "\n";
        return -1;
    }

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f};

    float colors[] = {
        1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f};

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    unsigned int pointsBuffer;
    glGenBuffers(1, &pointsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, pointsBuffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    unsigned int colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), colors, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    std::string vertexShader{};
    std::string fragmentShader{};

    readShader(vertexShader, VERTEX_SHADER_PATH);
    readShader(fragmentShader, FRAGMENT_SHADER_PATH);

    const char *vertShader = vertexShader.c_str();
    const char *fragShader = fragmentShader.c_str();

    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertShader, NULL);
    glCompileShader(vs);
    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragShader, NULL);
    glCompileShader(fs);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fs);
    glAttachShader(shaderProgram, vs);
    glLinkProgram(shaderProgram);

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

void readShader(std::string &shader, std::string shaderPath)
{
    std::ifstream vertexShaderSource(shaderPath);

    if (vertexShaderSource)
    {
        std::ostringstream ss;
        ss << vertexShaderSource.rdbuf(); // reading data
        shader = ss.str();
    }
}

int init(GLFWwindow **window)
{
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    *window = glfwCreateWindow(800, 600, "Triangles", NULL, NULL);

    if (!(*window))
    {
        std::cout << "Failed to create the GLFW Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    return 0;
}
