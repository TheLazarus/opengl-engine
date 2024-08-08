#include "Shader.hpp"

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    std::string vertexShaderCode{};
    std::string fragShaderCode{};

    std::ifstream vertexShaderIStream{}, fragShaderIStream{};

    vertexShaderIStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragShaderIStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertexShaderIStream.open(vertexShaderPath);
        fragShaderIStream.open(fragmentShaderPath);

        std::stringstream vertexShaderSStream{}, fragShaderSStream{};

        vertexShaderSStream << vertexShaderIStream.rdbuf();
        fragShaderSStream << fragShaderIStream.rdbuf();

        vertexShaderIStream.close();
        fragShaderIStream.close();

        vertexShaderCode = vertexShaderSStream.str();
        fragShaderCode = fragShaderSStream.str();
    }

    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR :: SHADER :: Unable to read shader file source" << std::endl;
    }

    const char *vShaderFinal = vertexShaderCode.c_str();
    const char *fShaderFinal = fragShaderCode.c_str();

    unsigned int vShaderObj{}, fShaderObj{};
    int success;
    char infoLog[512];

    vShaderObj = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShaderObj, 1, &vShaderFinal, NULL);
    glCompileShader(vShaderObj);

    glGetShaderiv(vShaderObj, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vShaderObj, 512, NULL, infoLog);
        std::cout << "ERROR :: VERTEX SHADER COMPILATION FAILED :: " << infoLog << std::endl;
    }

    fShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShaderObj, 1, &fShaderFinal, NULL);
    glCompileShader(fShaderObj);

    glGetShaderiv(fShaderObj, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fShaderObj, 512, NULL, infoLog);
        std::cout << "ERROR :: FRAGMENT SHADER COMPILATION FAILED :: " << infoLog << std::endl;
    }

    m_programId = glCreateProgram();
    glAttachShader(m_programId, vShaderObj);
    glAttachShader(m_programId, fShaderObj);
    glLinkProgram(m_programId);

    glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED " << infoLog << std::endl;
    }

    glDeleteShader(vShaderObj);
    glDeleteShader(fShaderObj);
}

void Shader::use()
{

    glUseProgram(m_programId);
}
