#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 translationMatrix;

void main() {
    gl_Position = tvec4(pos.xyz, 1.0f);
}