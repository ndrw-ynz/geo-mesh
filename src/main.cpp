#include "Engine/Engine.h"
#include "UI/TextUI.h"
#include "World/World.h"

#include <GLFW/glfw3.h>

int main() {
    Engine::Init();

    // render loop
    // -----------
    while (Engine::EngineActive()) {
        Engine::BeginFrame();

        std::cout << World::GetDeltaTime() << "ms (" << World::GetFPS() << "FPS)" << std::endl;

        Engine::Update();

        Engine::EndFrame();
    }

    TextUI::GetTextUI().GetMesh2DBuffer().DeleteBuffers();
    World::GetTerrain().GetTerrainMesh().GetMeshBuffer().DeleteBuffers();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
