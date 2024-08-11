#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;

out vec4 out_color;
out vec2 out_texCoord;

uniform mat4 translationMatrix;

void main() {
    gl_Position = translationMatrix * vec4(pos, 1.0f);
    // gl_Position = vec4(pos, 1.0f);
    out_color = vec4(color, 1.0f);

}