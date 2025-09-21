#include "GLFWIntegration.h"
#include "GLFW/glfw3.h"

namespace GLFWIntegration {

int g_windowWidth = 800;
int g_windowHeight = 600;
GLFWwindow *g_window;

bool Init() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    g_window = glfwCreateWindow(g_windowWidth, g_windowHeight, "GeoMesh", NULL, NULL);
    if (g_window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(g_window);
    glfwSetFramebufferSizeCallback(g_window, framebuffer_size_callback);

    glfwSetInputMode(g_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }
    return true;
}

void BeginFrame() { glfwPollEvents(); }

void EndFrame() { glfwSwapBuffers(g_window); }

int GetWindowWidth() { return g_windowWidth; }
int GetWindowHeight() { return g_windowHeight; }
GLFWwindow *GetWindowPointer() { return g_window; }

void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }
} // namespace GLFWIntegration
