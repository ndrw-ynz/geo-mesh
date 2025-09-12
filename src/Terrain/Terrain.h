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
    // TODO: add more relevant data from the terrain (ex. rez, width,height)

    void Init(int width, int height);
    Mesh &GetTerrainMesh() { return terrainMesh; }

  private:
    Mesh terrainMesh;
};
