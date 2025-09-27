#include "Renderer.h"
#include "Settings/Settings.h"

namespace Renderer {

void InitTerrain() {

    Shader *terrainShader = AssetManager::GetShader("terrainShader");
    int numBiomes = 5;
    terrainShader->use();
    terrainShader->setInt("uNumBiomes", numBiomes);

    terrainShader->setVec3("uLightDir", glm::vec3(-1.0f, -1.0f, 1.0f));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
}

void TerrainPass() {
    glEnable(GL_DEPTH_TEST);

    Shader *terrainShader = AssetManager::GetShader("terrainShader");
    Texture *icelandTexture = AssetManager::GetTexture("Iceland HeightMap");
    Terrain &terrain = World::GetTerrain();

    terrainShader->setVec3("uViewPos", World::GetNavigator().GetCamera().Position);
    terrainShader->use();

    // Lambertian shading, uncomment lines to experiment
    // float t = glfwGetTime();
    // terrainShader->setVec3("uLightDir", glm::vec3(cos(t * 2.0), sin(t * 2.0), 1.0f));
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, icelandTexture->GetHandle());

    glm::mat4 projection =
        glm::perspective(glm::radians(World::GetNavigator().GetCamera().Zoom),
                         (float)GLFWIntegration::GetWindowWidth() / (float)GLFWIntegration::GetWindowHeight(),
                         0.1f,
                         100000.0f);
    glm::mat4 view = World::GetNavigator().GetCamera().GetViewMatrix();
    glm::mat4 model = glm::mat4(1.0f);
    terrainShader->setMat4("projection", projection);
    terrainShader->setMat4("view", view);
    terrainShader->setMat4("model", model);
    terrainShader->setInt("renderMode", Engine::GetDEMRenderMode());

    // Dynamic LOD tessellation params
    terrainShader->setInt("uMinTessLevel", Settings::GetMinTessLevel());
    terrainShader->setInt("uMaxTessLevel", Settings::GetMaxTessLevel());
    terrainShader->setFloat("uMinLODDistance", Settings::GetMinLODDistance());
    terrainShader->setFloat("uMaxLODDistance", Settings::GetMaxLODDistance());
    // Lighting/shading params
    terrainShader->setVec3("uLightColor", Settings::GetLightColor());
    terrainShader->setFloat("uAmbientStrength", Settings::GetAmbientStrength());
    // Biome params
    terrainShader->setVec3Array("uBiomeColors", Settings::GetBiomeColors().data(), 5);
    terrainShader->setFloatArray("uBiomeHeights", Settings::GetBiomeHeights().data(), 5);

    glBindVertexArray(terrain.GetTerrainMesh().GetMeshBuffer().GetVAO());
    // toggle wireframe mode
    switch (Engine::GetDEMDisplayMode()) {
    case Engine::DEMDisplayMode::FILL:
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;
    case Engine::DEMDisplayMode::WIREFRAME:
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        break;
    }

    glDrawArrays(GL_PATCHES, 0, 4 * 20 * 20);
}
} // namespace Renderer
