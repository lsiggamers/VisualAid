#pragma once
#include "globalFunc.hpp"
#include <vector>

extern ScreenPosition windowSize;
extern bool globalShutoff;
extern int selectedBackground;
extern std::vector<Texture2D> backgroundTextures;

void importAppSettings();