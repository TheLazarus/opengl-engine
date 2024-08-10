#include "Texture.hpp"

Texture::Texture()
{
    glGenTextures(1, &id);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::source(const char *texturePath) const
{
    stbi_set_flip_vertically_on_load(1);
    int width{}, height{}, channels{};

    unsigned char *data = stbi_load(texturePath, &width, &height, &channels, 0);

    if (data == NULL)
    {
        std::cout << "ERROR :: Failed to Load Texture File!" << std::endl;
        return -1;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    unbind();

    return 0;
}

void Texture::del() const
{
    glDeleteTextures(1, &id);
}