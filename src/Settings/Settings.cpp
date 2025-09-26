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

int &GetMinTessLevel() { return g_minTessLevel; }
int &GetMaxTessLevel() { return g_maxTessLevel; }
float &GetMinLODDistance() { return g_minLODDistance; }
float &GetMaxLODDistance() { return g_maxLODDistance; }
float &GetAmbientStrength() { return g_ambientStrength; }
glm::vec3 &GetLightColor() { return g_lightColor; }
} // namespace Settings
