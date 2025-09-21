#include "Terrain.h"
#include "Core/Mesh.h"

void Terrain::Init(int width, int height) {
    // Generating patches of 4 vertices
    std::vector<Vertex> vertices;
    int rez = 20;
    float widthOffset = -width / 2.0f;
    float heightOffset = -height / 2.0f;
    for (int i = 0; i < rez; i++) {
        for (int j = 0; j < rez; j++) {
            // Top left vertex of Patch
            float vx_1 = widthOffset + width * i / (float)rez;
            float vy_1 = 0.0f;
            float vz_1 = heightOffset + height * j / (float)rez;
            float u_1 = i / (float)rez;
            float v_1 = j / (float)rez;
            vertices.push_back(Vertex(glm::vec3(vx_1, vy_1, vz_1), glm::vec2(u_1, v_1)));

            // Top right vertex of Patch
            float vx_2 = widthOffset + width * (i + 1) / (float)rez;
            float vy_2 = 0.0f;
            float vz_2 = heightOffset + height * j / (float)rez;
            float u_2 = (i + 1) / (float)rez;
            float v_2 = j / (float)rez;
            vertices.push_back(Vertex(glm::vec3(vx_2, vy_2, vz_2), glm::vec2(u_2, v_2)));

            // Bottom left vertex of Patch
            float vx_3 = widthOffset + width * i / (float)rez;
            float vy_3 = 0.0f;
            float vz_3 = heightOffset + height * (j + 1) / (float)rez;
            float u_3 = i / (float)rez;
            float v_3 = (j + 1) / (float)rez;
            vertices.push_back(Vertex(glm::vec3(vx_3, vy_3, vz_3), glm::vec2(u_3, v_3)));

            // Bottom right vertex of Patch
            float vx_4 = widthOffset + width * (i + 1) / (float)rez;
            float vy_4 = 0.0f;
            float vz_4 = heightOffset + height * (j + 1) / (float)rez;
            float u_4 = (i + 1) / (float)rez;
            float v_4 = (j + 1) / (float)rez;
            vertices.push_back(Vertex(glm::vec3(vx_4, vy_4, vz_4), glm::vec2(u_4, v_4)));
        }
    }
    std::cout << "Loaded " << rez * rez << " patches of 4 control points each" << std::endl;
    std::cout << "Processing " << rez * rez * 4 << " vertices in vertex shader" << std::endl;

    numStrips = (height - 1) / rez;
    numVertsPerStrip = (width / rez) * 2;
    std::cout << "Created lattice of " << numStrips << " strips with " << numVertsPerStrip << " triangles each"
              << std::endl;
    std::cout << "Created " << numStrips * numVertsPerStrip << " triangles total" << std::endl;

    terrainMesh = Mesh(vertices);
}
