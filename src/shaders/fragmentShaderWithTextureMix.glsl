#version 330 core

uniform sampler2D texture1;
uniform sampler2D texture2;

in vec2 out_texCoord;

out vec4 FragColor;

void main() {

    FragColor = mix(texture(texture1, out_texCoord), texture(texture2,out_texCoord ), 0.5);
}