#version 330 core

out vec4 FragColor;

in vec2 o_textureCoordinates;

uniform sampler2D wallTexture;

void main() {
    FragColor = texture(wallTexture, o_textureCoordinates);
}


