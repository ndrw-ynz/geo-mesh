#include "Mesh2DBuffer.h"

void Mesh2DBuffer::AllocateBuffers(size_t vertexCount) {
    GLsizei requestedVertexCount = static_cast<GLsizei>(vertexCount);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    m_EBO = 0;

    glBindVertexArray(m_VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * requestedVertexCount, nullptr, GL_DYNAMIC_DRAW);

    // Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, uv));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh2DBuffer::AllocateBuffers(size_t vertexCount, size_t indexCount) {
    GLsizei requestedVertexCount = static_cast<GLsizei>(vertexCount);
    GLsizei requestedIndexCount = static_cast<GLsizei>(indexCount);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    // Vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * requestedVertexCount, nullptr, GL_DYNAMIC_DRAW);

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * requestedIndexCount, nullptr, GL_DYNAMIC_DRAW);

    // Vertex Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, uv));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh2DBuffer::UpdateBuffers(const std::vector<Vertex2D> &vertices) {
    GLsizei newVertexCount = static_cast<GLsizei>(vertices.size());

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * newVertexCount, vertices.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh2DBuffer::UpdateBuffers(const std::vector<Vertex2D> &vertices, const std::vector<uint32_t> &indices) {
    GLsizei newVertexCount = static_cast<GLsizei>(vertices.size());
    GLsizei newIndexCount = static_cast<GLsizei>(indices.size());

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * newVertexCount, vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * newIndexCount, indices.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh2DBuffer::DeleteBuffers() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);

    m_VAO = 0;
    m_VBO = 0;
    m_EBO = 0;
}
