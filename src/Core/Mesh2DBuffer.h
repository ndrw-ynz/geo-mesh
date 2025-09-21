#pragma once
#include <glad/glad.h>
#include <vector>
#include <cstdint>

#include "Common/Types.h"

class Mesh2DBuffer {
  public:
    void AllocateBuffers(size_t vertexCount);
    void AllocateBuffers(size_t vertexCount, size_t indexCount);
    void UpdateBuffers(const std::vector<Vertex2D> &vertices);
    void UpdateBuffers(const std::vector<Vertex2D> &vertices, const std::vector<uint32_t> &indices);
    void DeleteBuffers();
    const GLuint GetVAO() const { return m_VAO; }
    const GLuint GetVBO() const { return m_VBO; }
    const GLuint GetEBO() const { return m_EBO; }

  private:
    GLuint m_VAO;
    GLuint m_VBO;
    GLuint m_EBO;
    int m_allocatedVertexCount;
    int m_allocatedIndexCount;
};
