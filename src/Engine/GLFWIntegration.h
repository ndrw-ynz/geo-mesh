#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace GLFWIntegration {
bool Init();
void BeginFrame();
void EndFrame();
int GetWindowWidth();
int GetWindowHeight();
GLFWwindow *GetWindowPointer();
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
} // namespace GLFWIntegration
