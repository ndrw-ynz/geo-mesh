#include "Terrain.h"
#include "Core/Mesh.h"

void Terrain::Init() {
    // Load DEM data

    // Extracting coordinates from DEM data
    int width, height, nrChannels;
    unsigned char *data = stbi_load("data/DEM/iceland_heightmap.png", &width, &height, &nrChannels, 0);
    if (data) {
        std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    std::vector<Vertex> vertices;
    float yScale = 64.0f / 256.0f, yShift = 16.0f;
    int rez = 1;
    unsigned bytePerPixel = nrChannels;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char *pixelOffset = data + (j + width * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];

            // vertex
            float vx = -height / 2.0f + height * i / (float)height;
            float vy = (int)y * yScale - yShift;
            float vz = -width / 2.0f + width * j / (float)width;
            vertices.push_back(Vertex(glm::vec3(vx, vy, vz)));

            // vertices.push_back(-height / 2.0f + height * i / (float)height); // vx
            // vertices.push_back((int)y * yScale - yShift);                    // vy
            // vertices.push_back(-width / 2.0f + width * j / (float)width);    // vz
        }
    }
    std::cout << "Loaded " << vertices.size() / 3 << " vertices" << std::endl;
    stbi_image_free(data);

    std::vector<uint32_t> indices;
    for (uint32_t i = 0; i < height - 1; i += rez) {
        for (uint32_t j = 0; j < width; j += rez) {
            for (uint32_t k = 0; k < 2; k++) {
                indices.push_back(j + width * (i + k * rez));
            }
        }
    }
    std::cout << "Loaded " << indices.size() << " indices" << std::endl;

    numStrips = (height - 1) / rez;
    numVertsPerStrip = (width / rez) * 2;
    std::cout << "Created lattice of " << numStrips << " strips with " << numVertsPerStrip << " triangles each"
              << std::endl;
    std::cout << "Created " << numStrips * numVertsPerStrip << " triangles total" << std::endl;

    terrainMesh = Mesh(vertices, indices);

    std::cout << "Index buffer size: " << terrainMesh.GetIndices().size() << std::endl;
    std::cout << "Expected: " << numStrips * numVertsPerStrip << std::endl;
}
