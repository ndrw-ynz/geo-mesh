#pragma once
#include "AssetManager/AssetManager.h"
#include "Engine/GLFWIntegration.h"
#include "World/World.h"
#include "Engine/Engine.h"
#include "Engine/GLFWIntegration.h"
#include "UI/TextUI.h"
#include "Settings/Settings.h"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace Renderer {

void Init();
void InitText();
void InitTerrain();
void Render();

// Render passes
void TextPass();
void TerrainPass();
void ImGuiPass();

// Text
void RenderText(
    Shader &shader, Mesh2DBuffer &textMesh2DBuffer, std::string text, float x, float y, float scale, glm::vec3 color);
} // namespace Renderer
