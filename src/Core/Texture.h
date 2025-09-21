#pragma once
#include <glad/glad.h>

class Texture {
  public:
    Texture() = default;
    Texture(int width, int height, void *data);
    void SetTextureMinFilter(GLint minFilter);
    void SetTextureMaxFilter(GLint maxFilter);
    void SetTextureSWrapping(GLint SWrapping);
    void SetTextureTWrapping(GLint TWrapping);
    GLuint &GetHandle();
    int GetWidth();
    int GetHeight();

  private:
    GLuint m_handle = 0;
    void *m_data = nullptr;
    int m_width = 0;
    int m_height = 0;
};
