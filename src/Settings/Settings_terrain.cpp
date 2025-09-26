#include "Settings.h"
#include "imgui.h"

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

    if (ImGui::CollapsingHeader("Lighting")) {
        ImGui::ColorPicker3("Directional Light Color",
                            glm::value_ptr(GetLightColor()),
                            ImGuiColorEditFlags_PickerHueBar | ImGuiColorEditFlags_NoSidePreview |
                                ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoAlpha);

        ImGui::Text("Shading Parameters");
        ImGui::SliderFloat("Ambient Strength", &GetAmbientStrength(), 0.0f, 1.0f);
    }

    ImGui::End();
}

} // namespace Settings
