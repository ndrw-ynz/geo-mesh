#pragma once
#include "Navigator/Navigator.h"
#include "AssetManager/AssetManager.h"
#include "Terrain/Terrain.h"

#include <GLFW/glfw3.h>

namespace World {
void Init();
void Update();
void Cleanup();
float GetDeltaTime();
int GetFPS();
Navigator &GetNavigator();
Terrain &GetTerrain();
} // namespace World
