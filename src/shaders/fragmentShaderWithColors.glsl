#version 330 core

out vec4 FragColor;

in vec4 out_color;
in vec2 out_texCoord;

uniform sampler2D ourTexture;

void main() {
    // texture (TEXTURE_OBJECT_SAMPLER, VEC2)
    FragColor = texture(ourTexture, out_texCoord);
}