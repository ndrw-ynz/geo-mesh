#pragma once
#include <GLFW/glfw3.h>

namespace Input {
void Init(GLFWwindow *window);
void Update();

bool KeyPressed(unsigned int keycode);
int GetMouseOffsetX();
int GetMouseOffsetY();
int GetScrollWheelValue();
} // namespace Input
