#pragma once

#include "Core/Mesh.h"
#include "Common/Types.h"

#include <stb_image.h>
#include <iostream>

class Terrain {
  public:
    // read stbi, and create vertex and indices normals etc.
    int numStrips;
    int numVertsPerStrip;

    void Init();
    Mesh &GetTerrainMesh() { return terrainMesh; }

  private:
    Mesh terrainMesh;
};
