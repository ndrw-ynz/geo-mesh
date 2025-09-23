#include "Renderer.h"

namespace Renderer {

void Init() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    InitText();
    InitTerrain();
}
void Render() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    TerrainPass();
    TextPass();
    ImGuiPass();
}
} // namespace Renderer
