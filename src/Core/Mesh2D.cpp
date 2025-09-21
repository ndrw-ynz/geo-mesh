#include "Mesh2D.h"

Mesh2D::Mesh2D(std::vector<Vertex2D> vertices) : m_vertices{ vertices } {
    m_mesh2DBuffer.AllocateBuffers(vertices.size());
    m_mesh2DBuffer.UpdateBuffers(vertices);
}
Mesh2D::Mesh2D(std::vector<Vertex2D> vertices, std::vector<uint32_t> indices)
    : m_vertices{ vertices }, m_indices{ indices }, m_mesh2DBuffer{} {
    m_mesh2DBuffer.AllocateBuffers(vertices.size(), indices.size());
    m_mesh2DBuffer.UpdateBuffers(vertices, indices);
}
