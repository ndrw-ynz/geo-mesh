#include "Terrain/Terrain.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Graphics/Camera.h"
#include "Graphics/Shader.h"

#include <iostream>
#include <map>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int modifiers);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color);

// modes for rendering DEM
enum DEMDisplayMode { FILL, WIREFRAME };
enum DEMRenderMode { GRAYSCALE, BIOME };

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
DEMDisplayMode demDisplayMode;
DEMRenderMode demRenderMode;

// Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
Camera camera(glm::vec3(67.0f, 50.5f, 169.9f), glm::vec3(0.0f, 1.0f, 0.0f), -128.1f, -42.4f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;        // Size of glyph
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

std::map<GLchar, Character> Characters;
unsigned int cVAO, cVBO;

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // build and compile our shader program
    // ------------------------------------
    Shader textShader("data/shaders/text.vs.glsl", "data/shaders/text.fs.glsl");
    Shader terrainShader("data/shaders/terrain.vs.glsl",
                         "data/shaders/terrain.fs.glsl",
                         nullptr,
                         "data/shaders/terrain.tcs.glsl",
                         "data/shaders/terrain.tes.glsl");

    // ------------------------------------
    // Text Rendering
    // ------------------------------------
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "data/fonts/MxPlus_IBM_VGA_8x16.ttf", 0, &face)) {
        std::cout << "ERROR:FREETYPE: Failed to load font" << std::endl;
        return -1;
    } else {
        FT_Set_Pixel_Sizes(face, 0, 36);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++) {
            // Load character glyph
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
                continue;
            }
            // generate texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D,
                         0,
                         GL_RED,
                         face->glyph->bitmap.width,
                         face->glyph->bitmap.rows,
                         0,
                         GL_RED,
                         GL_UNSIGNED_BYTE,
                         face->glyph->bitmap.buffer);
            // set texture options
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // now store character for later use
            Character character = { texture,
                                    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                                    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                                    static_cast<unsigned int>(face->glyph->advance.x) };
            Characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // configure VAO/VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &cVAO);
    glGenBuffers(1, &cVBO);
    glBindVertexArray(cVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    textShader.use();
    glm::mat4 textProjection = glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT);
    textShader.setMat4("projection", textProjection);

    // ------------------------------------
    // DEM
    // ------------------------------------
    unsigned int textureDEM;
    glGenTextures(1, &textureDEM);
    glBindTexture(GL_TEXTURE_2D, textureDEM);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Extracting coordinates from DEM data
    int width, height, nrChannels;
    unsigned char *data = stbi_load("data/DEM/iceland_heightmap.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        terrainShader.setInt("heightMap", 0);
        std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    Terrain terrain{};
    terrain.Init(width, height);
    int numBiomes = 5;
    float biomeHeights[5] = { 0.2f, 0.4f, 0.6f, 0.8f, 1.1f };
    glm::vec3 biomeColors[5] = {
        glm::vec3(0.1f, 0.1f, 0.3f),  // deep frozen water
        glm::vec3(0.3f, 0.5f, 0.7f),  // glacial blue
        glm::vec3(0.6f, 0.7f, 0.8f),  // icy rock
        glm::vec3(0.8f, 0.85f, 0.9f), // compacted snow
        glm::vec3(1.0f, 1.0f, 1.0f)   // pure snow
    };
    terrainShader.use();
    terrainShader.setInt("uNumBiomes", numBiomes);
    terrainShader.setFloatArray("uBiomeHeights", biomeHeights, numBiomes);
    terrainShader.setVec3Array("uBiomeColors", biomeColors, numBiomes);

    terrainShader.setVec3("uLightColor", glm::vec3(1.0f, 1.0f, 1.0f));
    terrainShader.setFloat("uAmbientStrength", 0.1f);
    terrainShader.setFloat("uSpecularStrength", 0.5f);
    terrainShader.setVec3("uLightDir", glm::vec3(-1.0f, -1.0f, 1.0f));
    terrainShader.setVec3("uViewPos", camera.Position);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        int fps = 1.0f / deltaTime;

        std::cout << deltaTime << "ms (" << fps << "FPS)" << std::endl;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        // render DEM
        // --------------------
        terrainShader.use();
        // Lambertian shading, uncomment lines to experiment
        // float t = glfwGetTime();
        // terrainShader.setVec3("uLightDir", glm::vec3(cos(t * 2.0), sin(t * 2.0), 1.0f));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureDEM);

        // view/projection transformations
        glm::mat4 projection =
            glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        terrainShader.setMat4("projection", projection);
        terrainShader.setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        terrainShader.setMat4("model", model);

        glBindVertexArray(terrain.GetTerrainMesh().GetMeshBuffer().GetVAO());
        // toggle wireframe mode
        switch (demDisplayMode) {
        case DEMDisplayMode::FILL:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
        case DEMDisplayMode::WIREFRAME:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
        }
        terrainShader.setInt("renderMode", demRenderMode);
        glDrawArrays(GL_PATCHES, 0, 4 * 20 * 20);

        // render Text
        // --------------------
        glDisable(GL_DEPTH_TEST);
        RenderText(textShader, "FPS: " + std::to_string(fps), 15.0f, 15.0f, 1.0f, glm::vec3(0.5, 0.8f, 0.2f));
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse
        // moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cVAO);
    glDeleteBuffers(1, &cVBO);
    terrain.GetTerrainMesh().GetMeshBuffer().DeleteBuffers();

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this
// frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width
    // and height will be significantly larger than specified on retina
    // displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever a key event occurs, this callback is called
// ---------------------------------------------------------------------------------------------
void key_callback(GLFWwindow *window, int key, int scancode, int action, int modifiers) {
    if (action == GLFW_PRESS) {
        switch (key) {
        case GLFW_KEY_SPACE:
            demDisplayMode = DEMDisplayMode::WIREFRAME;
            break;
        case GLFW_KEY_F:
            demDisplayMode = DEMDisplayMode::FILL;
            break;
        case GLFW_KEY_G:
            demRenderMode = DEMRenderMode::GRAYSCALE;
            break;
        case GLFW_KEY_B:
            demRenderMode = DEMRenderMode::BIOME;
            break;
        default:
            break;
        }
    }
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

// render line of text
// -------------------
void RenderText(Shader &shader, std::string text, float x, float y, float scale, glm::vec3 color) {
    // avoid rendering text as wireframe
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // activate corresponding render state
    float copyX = x;
    shader.use();
    glUniform3f(glGetUniformLocation(shader.ID, "textColor"), color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(cVAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) {
        Character ch = Characters[*c];
        if (*c == 'n') {
            y -= ((ch.Size.y)) * 1.3 * scale;
            x = copyX;
        } else if (*c == ' ') {
            x += (ch.Advance >> 6) * scale;
        } else {

            float xpos = x + ch.Bearing.x * scale;
            float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;
            // update VBO for each character
            float vertices[6][4] = { { xpos, ypos + h, 0.0f, 0.0f },    { xpos, ypos, 0.0f, 1.0f },
                                     { xpos + w, ypos, 1.0f, 1.0f },

                                     { xpos, ypos + h, 0.0f, 0.0f },    { xpos + w, ypos, 1.0f, 1.0f },
                                     { xpos + w, ypos + h, 1.0f, 0.0f } };
            // render glyph texture over quad
            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            // update content of VBO memory
            glBindBuffer(GL_ARRAY_BUFFER, cVBO);
            glBufferSubData(
                GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            // render quad
            glDrawArrays(GL_TRIANGLES, 0, 6);
            // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
            x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th
                                            // pixels by 64 to get amount of pixels))
        }
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
