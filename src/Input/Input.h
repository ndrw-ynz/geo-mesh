#pragma once
#include <GLFW/glfw3.h>

namespace Input {
void Init(GLFWwindow *window);
void Update();

bool KeyDown(unsigned int keycode);
bool KeyPress(unsigned int keycode);
int GetMouseOffsetX();
int GetMouseOffsetY();
int GetScrollWheelValue();
} // namespace Input
