#version 330 core

layout (location = 0) in vec3 pos;


uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;


void main() {
    vec4 newPosition =   u_view * u_model * vec4(pos, 1.0f);
    gl_Position = newPosition;
}