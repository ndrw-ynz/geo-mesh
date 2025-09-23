#include "Engine.h"

namespace Engine {
DEMDisplayMode g_demDisplayMode;
DEMRenderMode g_demRenderMode;

void Init() {
    GLFWIntegration::Init();

    Input::Init(GLFWIntegration::GetWindowPointer());
    AssetManager::Init();
    World::Init();
    TextUI::Init();
    Renderer::Init();
    ImGuiLayer::Init();
}

void BeginFrame() { GLFWIntegration::BeginFrame(); }

void Update() {
    Input::Update();
    ProcessKeyEvents();
    World::Update();
    Renderer::Render();
}

void EndFrame() { GLFWIntegration::EndFrame(); }

void ProcessKeyEvents() {
    Camera &navigatorCamera = World::GetNavigator().GetCamera();
    GLFWwindow *window = GLFWIntegration::GetWindowPointer();
    int cursorMode = glfwGetInputMode(window, GLFW_CURSOR);

    if (Input::KeyPressed(GLFW_KEY_ESCAPE))
        glfwSetWindowShouldClose(GLFWIntegration::GetWindowPointer(), true);
    if (Input::KeyPressed(GLFW_KEY_W))
        navigatorCamera.ProcessKeyboard(FORWARD, World::GetDeltaTime());
    if (Input::KeyPressed(GLFW_KEY_S))
        navigatorCamera.ProcessKeyboard(BACKWARD, World::GetDeltaTime());
    if (Input::KeyPressed(GLFW_KEY_A))
        navigatorCamera.ProcessKeyboard(LEFT, World::GetDeltaTime());
    if (Input::KeyPressed(GLFW_KEY_D))
        navigatorCamera.ProcessKeyboard(RIGHT, World::GetDeltaTime());
    if (Input::KeyPressed(GLFW_KEY_Q))
        navigatorCamera.ProcessKeyboard(UP, World::GetDeltaTime());
    if (Input::KeyPressed(GLFW_KEY_E))
        navigatorCamera.ProcessKeyboard(DOWN, World::GetDeltaTime());

    if (Input::KeyPressed(GLFW_KEY_SPACE))
        g_demDisplayMode = DEMDisplayMode::WIREFRAME;
    if (Input::KeyPressed(GLFW_KEY_F))
        g_demDisplayMode = DEMDisplayMode::FILL;
    if (Input::KeyPressed(GLFW_KEY_G))
        g_demRenderMode = DEMRenderMode::GRAYSCALE;
    if (Input::KeyPressed(GLFW_KEY_B))
        g_demRenderMode = DEMRenderMode::BIOME;

    if (Input::KeyPressed(GLFW_KEY_M)) {
        switch (cursorMode) {
        case GLFW_CURSOR_DISABLED:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            break;
        case GLFW_CURSOR_NORMAL:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            break;
        }
    }

    if (cursorMode == GLFW_CURSOR_DISABLED) {
        navigatorCamera.ProcessMouseMovement(Input::GetMouseOffsetX(), Input::GetMouseOffsetY());
        navigatorCamera.ProcessMouseScroll(static_cast<float>(Input::GetScrollWheelValue()));
    }
}

DEMDisplayMode GetDEMDisplayMode() { return g_demDisplayMode; }
DEMRenderMode GetDEMRenderMode() { return g_demRenderMode; }
bool EngineActive() { return !glfwWindowShouldClose(GLFWIntegration::GetWindowPointer()); }

} // namespace Engine
