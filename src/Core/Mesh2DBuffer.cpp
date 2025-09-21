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
    m_allocatedVertexCount = vertexCount;

    // Vertex Attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, position));
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
    m_allocatedVertexCount = vertexCount;

    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * requestedIndexCount, nullptr, GL_DYNAMIC_DRAW);
    m_allocatedIndexCount = indexCount;

    // Vertex Attributes
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, uv));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh2DBuffer::UpdateBuffers(const std::vector<Vertex2D> &vertices) {
    GLsizei newVertexCount = static_cast<GLsizei>(vertices.size());

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    if (newVertexCount > m_allocatedVertexCount) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * newVertexCount, vertices.data(), GL_DYNAMIC_DRAW);
    } else {
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex2D) * newVertexCount, vertices.data());
    }
    m_allocatedVertexCount = newVertexCount;

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh2DBuffer::UpdateBuffers(const std::vector<Vertex2D> &vertices, const std::vector<uint32_t> &indices) {
    GLsizei newVertexCount = static_cast<GLsizei>(vertices.size());
    GLsizei newIndexCount = static_cast<GLsizei>(indices.size());

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    if (newVertexCount > m_allocatedVertexCount) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2D) * newVertexCount, vertices.data(), GL_DYNAMIC_DRAW);
    } else {

        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex2D) * newVertexCount, vertices.data());
    }
    m_allocatedVertexCount = newVertexCount;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    if (newIndexCount > m_allocatedIndexCount) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * newIndexCount, indices.data(), GL_DYNAMIC_DRAW);
    } else {
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(uint32_t) * newIndexCount, vertices.data());
    }
    m_allocatedIndexCount = newIndexCount;

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
