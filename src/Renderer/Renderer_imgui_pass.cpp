#include "Renderer.h"
#include "Settings/Settings.h"

namespace Renderer {

void ImGuiPass() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (Settings::IsShown()) {
        Settings::CreateTerrainSettings();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
} // namespace Renderer
