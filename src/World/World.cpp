#include "World.h"

namespace World {
float g_deltaTime = 0.0f;
float g_lastFrame = 0.0f;
int g_fps = 0;

Navigator g_navigator;
Terrain g_terrain;

void Init() {
    g_navigator = Navigator(glm::vec3(67.0f, 50.5f, 169.9f), glm::vec3(0.0f, 1.0f, 0.0f), -128.1f, -42.4f);

    Texture *icelandTexture = AssetManager::GetTexture("Iceland HeightMap");
    g_terrain.Init(icelandTexture->GetWidth(), icelandTexture->GetHeight());
}

void Update() {
    float currentFrame = glfwGetTime();
    g_deltaTime = currentFrame - g_lastFrame;
    g_lastFrame = currentFrame;
    g_fps = 1.0f / g_deltaTime;
}

void Cleanup() { g_terrain.GetTerrainMesh().GetMeshBuffer().DeleteBuffers(); }
float GetDeltaTime() { return g_deltaTime; }
int GetFPS() { return g_fps; }

Navigator &GetNavigator() { return g_navigator; }
Terrain &GetTerrain() { return g_terrain; }
} // namespace World
