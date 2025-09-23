#include "Settings.h"

namespace Settings {

void CreateTerrainSettings() {
    ImGui::SetNextWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);
    ImGui::Begin("Terrain Render Settings");

    if (ImGui::CollapsingHeader("Dynamic Level of Detail (LOD)")) {
        // Tess min/max level params
        ImGui::Text("Tessellation Levels");
        ImGui::SliderInt("Min Tess Level", &GetMinTessLevel(), 4, 100);
        ImGui::SliderInt("Max Tess Level", &GetMaxTessLevel(), 100, 200);

        // Level of detail distance params
        ImGui::Text("LOD Distance");
        ImGui::SliderFloat("Min LOD Distance", &GetMinLODDistance(), 20, 100);
        ImGui::SliderFloat("Max LOD Distance", &GetMaxLODDistance(), 100, 800);
    }
    ImGui::End();
}

} // namespace Settings
