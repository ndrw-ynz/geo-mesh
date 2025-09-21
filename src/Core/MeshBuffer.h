#pragma once
#include <glad/glad.h>
#include <vector>
#include <cstdint>

#include "Common/Types.h"

class MeshBuffer {
  public:
    void AllocateBuffers(size_t vertexCount);
    void AllocateBuffers(size_t vertexCount, size_t indexCount);
    void UpdateBuffers(const std::vector<Vertex> &vertices);
    void UpdateBuffers(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);
    void DeleteBuffers();

    const GLuint GetVAO() const { return m_VAO; }
    const GLuint GetVBO() const { return m_VBO; }
    const GLuint GetEBO() const { return m_EBO; }

  private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
};
