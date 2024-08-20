#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 u_perspective;
uniform mat4 u_translation;


void main() {
    vec4 newPosition =  u_perspective * u_translation * vec4(pos, 1.0f);
    gl_Position = newPosition;
}