#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;

uniform mat4 u_perspective;


out vec2 o_texCoord;


void main() {
    vec4 newPosition = u_perspective * vec4(pos, 1.0f);
    gl_Position = newPosition;
    o_texCoord = texCoord;
}