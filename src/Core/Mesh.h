#pragma once

#include "Common/Types.h"
#include "Core/MeshBuffer.h"
#include <vector>

class Mesh {
  public:
    Mesh() = default;
    Mesh(std::vector<Vertex> vertices);
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);

    std::vector<Vertex> &GetVertices() { return m_vertices; }
    std::vector<uint32_t> &GetIndices() { return m_indices; }
    MeshBuffer &GetMeshBuffer() { return m_meshBuffer; }

  private:
    std::vector<Vertex> m_vertices;
    std::vector<uint32_t> m_indices;
    MeshBuffer m_meshBuffer;
};
