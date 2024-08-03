#ifndef APP_UTILS
#define APP_UTILS

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

void readShader(std::string &, const std::string);

void printShaderInfoLog(unsigned int);
void printProgramInfoLog(unsigned int);
void frameBufferSizeCb(GLFWwindow *window, int width, int height);
int init(GLFWwindow **window);

#endif