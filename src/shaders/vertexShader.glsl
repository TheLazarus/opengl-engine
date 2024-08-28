#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;


uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 o_color;


void main() {
    vec4 newPosition = u_projection * u_view * u_model * vec4(pos, 1.0f);
    gl_Position = newPosition;
    o_color = color;
}