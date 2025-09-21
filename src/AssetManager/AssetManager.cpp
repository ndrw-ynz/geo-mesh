#include "AssetManager.h"
#include "Core/Texture.h"
#include "Engine/GLFWIntegration.h"

namespace AssetManager {

std::unordered_map<std::string, std::unique_ptr<Shader>> g_shaders;
std::unordered_map<std::string, std::array<Character, 128>> g_fontCharacters;
std::unordered_map<std::string, Texture> g_textures;

void Init() {
    // Shaders
    AddShader("textShader", { "data/shaders/text.vs.glsl", "data/shaders/text.fs.glsl" });
    AddShader("terrainShader",
              { "data/shaders/terrain.vs.glsl",
                "data/shaders/terrain.fs.glsl",
                std::nullopt,
                "data/shaders/terrain.tcs.glsl",
                "data/shaders/terrain.tes.glsl" });

    // Font Characters
    AddFont("IBM VGA 8x16", "data/fonts/MxPlus_IBM_VGA_8x16.ttf");

    // Textures
    Texture *icelandTexture = AddTexture("Iceland HeightMap", "data/DEM/iceland_heightmap.png");
    icelandTexture->SetTextureSWrapping(GL_REPEAT);
    icelandTexture->SetTextureTWrapping(GL_REPEAT);
    icelandTexture->SetTextureMinFilter(GL_LINEAR_MIPMAP_LINEAR);
    icelandTexture->SetTextureMaxFilter(GL_LINEAR);
}

void Cleanup() {}

std::unordered_map<std::string, std::unique_ptr<Shader>> &GetShaders() { return g_shaders; }
std::unordered_map<std::string, std::array<Character, 128>> &GetFontCharacters() { return g_fontCharacters; }
std::unordered_map<std::string, Texture> &GetTextures() { return g_textures; }
} // namespace AssetManager
