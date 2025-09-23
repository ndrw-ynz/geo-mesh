#pragma once
#include "imgui.h"

namespace Settings {

void CreateTerrainSettings();

int &GetMinTessLevel();
int &GetMaxTessLevel();
float &GetMinLODDistance();
float &GetMaxLODDistance();
} // namespace Settings
