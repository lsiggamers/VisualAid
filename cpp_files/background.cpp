#include "background.hpp"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "raylib.h"

#include <vector>

void resizeAndUpload(Image& tmpImg) {
    ImageResize(&tmpImg, windowSize.x, windowSize.y);
    backgroundTextures.push_back(LoadTextureFromImage(tmpImg));
}


void loadBackgroundTextures() {
    Image BackGround = LoadImage("assets/background1.jpg");
    resizeAndUpload(BackGround);
    UnloadImage(BackGround);
    Image BackGround2 = LoadImage("assets/background2.jpg");
    resizeAndUpload(BackGround2);
    UnloadImage(BackGround2);
}

void drawBackground() {
    switch (selectedBackground) {
        case 1:
            DrawTexture(backgroundTextures[0], 0, 0, WHITE);
            break;
        default:
            DrawTexture(backgroundTextures[1], 0, 0, WHITE);
            break;
    }
}

void unloadBackgroundTextures() {
    for (const auto& texture : backgroundTextures) {
        UnloadTexture(texture);
    }
}