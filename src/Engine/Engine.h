#pragma once
#include "Engine/GLFWIntegration.h"
#include "Input/Input.h"
#include "Navigator/Navigator.h"
#include "World/World.h"
#include "AssetManager/AssetManager.h"
#include "Renderer/Renderer.h"
#include "UI/TextUI.h"

namespace Engine {
enum DEMDisplayMode { FILL, WIREFRAME };
enum DEMRenderMode { GRAYSCALE, BIOME };

void Init();
void BeginFrame();
void Update();
void EndFrame();
void ProcessKeyEvents();

DEMDisplayMode GetDEMDisplayMode();
DEMRenderMode GetDEMRenderMode();
bool EngineActive();
} // namespace Engine
