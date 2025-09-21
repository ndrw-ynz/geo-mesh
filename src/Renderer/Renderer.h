#pragma once
#include "AssetManager/AssetManager.h"
#include "Engine/GLFWIntegration.h"
#include "World/World.h"
#include "Engine/Engine.h"
#include "Engine/GLFWIntegration.h"
#include "UI/TextUI.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Renderer {

void Init();
void InitText();
void InitTerrain();
void Render();

// Render passes
void TextPass();
void TerrainPass();

// Text
void RenderText(
    Shader &shader, Mesh2DBuffer &textMesh2DBuffer, std::string text, float x, float y, float scale, glm::vec3 color);
} // namespace Renderer
