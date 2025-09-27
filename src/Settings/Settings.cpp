#include "Settings.h"

namespace Settings {

// Terrain tessellation parameters
int g_minTessLevel = 8;
int g_maxTessLevel = 100;
float g_minLODDistance = 20;
float g_maxLODDistance = 300;
// Terrain lighting parameters
float g_ambientStrength = 0.1;
glm::vec3 g_lightColor{ 1.0f, 1.0f, 1.0f };
// Biome parameters
std::vector<glm::vec3> g_biomeColors = {
    glm::vec3(0.1f, 0.1f, 0.3f),  // deep frozen water
    glm::vec3(0.3f, 0.5f, 0.7f),  // glacial blue
    glm::vec3(0.6f, 0.7f, 0.8f),  // icy rock
    glm::vec3(0.8f, 0.85f, 0.9f), // compacted snow
    glm::vec3(1.0f, 1.0f, 1.0f)   // pure snow
};
std::vector<float> g_biomeHeights = { 0.2f, 0.4f, 0.6f, 0.8f, 0.9f };

int &GetMinTessLevel() { return g_minTessLevel; }
int &GetMaxTessLevel() { return g_maxTessLevel; }
float &GetMinLODDistance() { return g_minLODDistance; }
float &GetMaxLODDistance() { return g_maxLODDistance; }
float &GetAmbientStrength() { return g_ambientStrength; }
glm::vec3 &GetLightColor() { return g_lightColor; }
std::vector<glm::vec3> &GetBiomeColors() { return g_biomeColors; }
std::vector<float> &GetBiomeHeights() { return g_biomeHeights; }
} // namespace Settings
