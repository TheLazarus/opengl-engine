#ifndef OG_APP_MAIN
#define OG_APP_MAIN

#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

// Constants
const std::string VERTEX_SHADER_PATH{"./shaders/vertexShader.shader"};
const std::string FRAGMENT_SHADER_PATH{"./shaders/fragmentShader.shader"};

// Functions

void readShader(std::string &, const std::string);

void printShaderInfoLog(unsigned int);
void printProgramInfoLog(unsigned int);
int init(GLFWwindow **window);

#endif