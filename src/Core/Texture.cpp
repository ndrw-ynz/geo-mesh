#include "Texture.h"

Texture::Texture(int width, int height, void *data) {
    glGenTextures(1, &m_handle);
    glBindTexture(GL_TEXTURE_2D, m_handle);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    m_width = width;
    m_height = height;
    m_data = data;

    glBindTexture(GL_TEXTURE_2D, 0);
}
void Texture::SetTextureMinFilter(GLint minFilter) {
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetTextureMaxFilter(GLint maxFilter) {
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, maxFilter);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetTextureSWrapping(GLint SWrapping) {
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, SWrapping);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::SetTextureTWrapping(GLint TWrapping) {
    glBindTexture(GL_TEXTURE_2D, m_handle);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TWrapping);
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint &Texture::GetHandle() { return m_handle; }

int Texture::GetWidth() { return m_width; }

int Texture::GetHeight() { return m_height; }
