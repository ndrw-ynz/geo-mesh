#include "Input.h"

namespace Input {
// Mouse: Position
int g_mouseX = 0;
int g_mouseY = 0;
int g_mouseOffsetX = 0;
int g_mouseOffsetY = 0;
int g_mouseXPrevFrame = 0;
int g_mouseYPrevFrame = 0;
// Mouse: Scroll Wheel
int g_scrollWheelValue = 0;
int g_scrollWheelOffsetY = 0;
// Keyboard
bool g_keyDown[372];
bool g_prevFrameKeyDown[372];
bool g_keyPress[372];

GLFWwindow *g_window;

void MouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset);

void Init(GLFWwindow *window) {
    g_window = window;
    glfwSetScrollCallback(g_window, MouseScrollCallback);
    double x, y;
    glfwGetCursorPos(g_window, &x, &y);
    g_mouseX = x;
    g_mouseY = y;
    g_mouseOffsetX = x;
    g_mouseOffsetY = y;
}

void Update() {
    // Update Mouse: Position
    g_mouseXPrevFrame = g_mouseX;
    g_mouseYPrevFrame = g_mouseY;
    double x, y;
    glfwGetCursorPos(g_window, &x, &y);
    g_mouseOffsetX = x - g_mouseX;
    g_mouseOffsetY = g_mouseY - y;
    g_mouseX = x;
    g_mouseY = y;

    // Update Mouse: Scroll Wheel
    g_scrollWheelValue = g_scrollWheelOffsetY;
    g_scrollWheelOffsetY = 0;

    // Update Keyboard
    for (int i = 32; i < 349; i++) {
        g_keyDown[i] = glfwGetKey(g_window, i) == GLFW_PRESS;
        g_keyPress[i] = g_keyDown[i] && !g_prevFrameKeyDown[i];

        g_prevFrameKeyDown[i] = g_keyDown[i];
    }
}

bool KeyDown(unsigned int keycode) { return g_keyDown[keycode]; }
bool KeyPress(unsigned int keycode) { return g_keyPress[keycode]; }

int GetMouseOffsetX() { return g_mouseOffsetX; }
int GetMouseOffsetY() { return g_mouseOffsetY; }
int GetScrollWheelValue() { return g_scrollWheelValue; }

void MouseScrollCallback(GLFWwindow *window, double xOffset, double yOffset) { g_scrollWheelOffsetY = (int)yOffset; }
} // namespace Input
