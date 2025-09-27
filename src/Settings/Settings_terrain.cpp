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

    if (ImGui::CollapsingHeader("Biome Mapping")) {
        ImGui::Text("Biome Layer Colors");
        auto &biomeColors = GetBiomeColors();
        for (int i = biomeColors.size() - 1; i >= 0; i--) {
            std::string label = "Biome Layer " + std::to_string(biomeColors.size() - i);
            label += (i == 0) ? " (Bottom)" : "";
            label += (i == biomeColors.size() - 1) ? " (Top)" : "";

            ImGui::ColorEdit3(label.c_str(), glm::value_ptr(biomeColors[i]));
        }

        ImGui::Text("Biome Heights");
        auto &biomeHeights = GetBiomeHeights();
        for (int i = biomeHeights.size() - 1; i >= 0; i--) {
            std::string label = "Biome Height Layer " + std::to_string(biomeHeights.size() - i);
            label += (i == 0) ? " (Bottom)" : "";
            label += (i == biomeHeights.size() - 1) ? " (Top)" : "";

            float minVal = (i == 0) ? 0.0f : biomeHeights[i - 1];
            float maxVal = (i == biomeHeights.size() - 1) ? 1.0f : biomeHeights[i + 1];

            ImGui::SliderFloat(label.c_str(), &biomeHeights[i], minVal, maxVal);
        }
    }

    ImGui::End();
}

} // namespace Settings
