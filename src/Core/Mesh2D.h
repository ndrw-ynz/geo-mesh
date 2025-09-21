#pragma once
#include "Common/Types.h"
#include "Core/Mesh2DBuffer.h"

#include <vector>

class Mesh2D {

  public:
    Mesh2D() = default;
    Mesh2D(std::vector<Vertex2D> vertices);
    Mesh2D(std::vector<Vertex2D> vertices, std::vector<uint32_t> indices);

    void AllocateMesh2DBuffers(int allocatedVertexCount);
    std::vector<Vertex2D> &GetVertices() { return m_vertices; }
    std::vector<uint32_t> &GetIndices() { return m_indices; }

    Mesh2DBuffer &GetMesh2DBuffer() { return m_mesh2DBuffer; }

  private:
    std::vector<Vertex2D> m_vertices;
    std::vector<uint32_t> m_indices;
    Mesh2DBuffer m_mesh2DBuffer;
};
