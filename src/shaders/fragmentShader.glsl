#version 330 core

out vec4 FragColor;
in vec2 o_texCoord;
in vec3 o_color;

uniform sampler2D u_tex;


void main() {
    FragColor = vec4(o_color, 1.0f);
    }


