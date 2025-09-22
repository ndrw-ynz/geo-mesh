#pragma once
#include "Engine/GLFWIntegration.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace ImGuiLayer {

void Init();
void Cleanup();
} // namespace ImGuiLayer
