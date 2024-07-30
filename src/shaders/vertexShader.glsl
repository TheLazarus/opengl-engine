#version 330 core

layout (position = 0) in vec3 vertexPosition;



void main() {
    gl_Position = vec4(vertexPosition, 1.0);
}

