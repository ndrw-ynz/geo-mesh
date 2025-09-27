#pragma once
#include "imgui.h"

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <string>

namespace Settings {

void CreateTerrainSettings();

int &GetMinTessLevel();
int &GetMaxTessLevel();
float &GetMinLODDistance();
float &GetMaxLODDistance();
float &GetAmbientStrength();
glm::vec3 &GetLightColor();
std::vector<glm::vec3> &GetBiomeColors();
std::vector<float> &GetBiomeHeights();
} // namespace Settings
