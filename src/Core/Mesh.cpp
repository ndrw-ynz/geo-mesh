#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
    : m_vertices{ vertices }, m_indices{ indices }, m_meshBuffer{} {
    m_meshBuffer.AllocateBuffers(vertices.size(), indices.size());
    m_meshBuffer.UpdateBuffers(vertices, indices);
}
