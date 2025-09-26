#pragma once
#include "imgui.h"

#include <glm/glm.hpp>
#include <glm/detail/type_vec.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Settings {

void CreateTerrainSettings();

int &GetMinTessLevel();
int &GetMaxTessLevel();
float &GetMinLODDistance();
float &GetMaxLODDistance();
float &GetAmbientStrength();
glm::vec3 &GetLightColor();
} // namespace Settings
