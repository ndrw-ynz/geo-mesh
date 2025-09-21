#include "TextUI.h"

namespace TextUI {
Mesh2D g_textUI;

void Init() { g_textUI.AllocateMesh2DBuffers(6); }

Mesh2D &GetTextUI() { return g_textUI; }
} // namespace TextUI
