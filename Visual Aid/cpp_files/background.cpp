#include "background.hpp"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "raylib.h"

static Texture2D backgroundTexture1 = { 0 };

void loadBackgroundTextures() {
    Image tmpIng = LoadImage("assets/background1.jpg");
    ImageResize(&tmpIng, windowSize.x, windowSize.y);
    backgroundTexture1 = LoadTextureFromImage(tmpIng);
    UnloadImage(tmpIng);
}

void drawBackground() {
    DrawTexture(backgroundTexture1, 0, 0, WHITE);
}

void unloadBackgroundTextures() {
    UnloadTexture(backgroundTexture1);
}