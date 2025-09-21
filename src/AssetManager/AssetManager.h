#pragma once
#include "Core/Texture.h"
#include "Graphics/Shader.h"
#include "Common/Types.h"
#include <memory>
#include <optional>
#include <string>
#include <map>
#include <unordered_map>
#include <array>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <stb_image.h>

namespace AssetManager {

void Init();
void Cleanup();

// Shaders
Shader *AddShader(const std::string &shaderName, const ShaderSourcePaths &sourcePaths);
Shader *GetShader(const std::string &shaderName);
std::unordered_map<std::string, std::unique_ptr<Shader>> &GetShaders();

// Fonts
bool AddFont(const std::string &fontName, const std::string &sourcePath);
std::array<Character, 128> &GetFont(const std::string &fontName);
std::unordered_map<std::string, std::array<Character, 128>> &GetFontCharacters();

// Textures
Texture *AddTexture(const std::string &textureName, const std::string &texturePath);
Texture *GetTexture(const std::string &textureName);
std::unordered_map<std::string, Texture> &GetTextures();
}; // namespace AssetManager
