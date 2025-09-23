#include "Settings.h"

namespace Settings {

// Terrain tessellation parameters
int g_minTessLevel = 8;
int g_maxTessLevel = 100;
float g_minLODDistance = 20;
float g_maxLODDistance = 300;

int &GetMinTessLevel() { return g_minTessLevel; }
int &GetMaxTessLevel() { return g_maxTessLevel; }
float &GetMinLODDistance() { return g_minLODDistance; }
float &GetMaxLODDistance() { return g_maxLODDistance; }
} // namespace Settings
