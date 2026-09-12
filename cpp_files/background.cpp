#include "background.hpp"
#include "globalFunc.hpp"
#include "globalSettings.hpp"
#include "raylib.h"

#include <vector>
#include <filesystem>
#include <algorithm>

void resizeAndUpload(Image& tmpImg) {
    ImageResize(&tmpImg, windowSize.x, windowSize.y);
    backgroundTextures.push_back(LoadTextureFromImage(tmpImg));
}


void loadBackgroundTextures() {
    namespace fs = std::filesystem;

    // Unload any previously loaded textures to avoid leaks
    unloadBackgroundTextures();
    backgroundTextures.clear();

    const fs::path imagesDir("assets/backgroundimages");
    if (!fs::exists(imagesDir) || !fs::is_directory(imagesDir)) {
        return;
    }

    for (const auto& entry : fs::directory_iterator(imagesDir)) {
        if (!entry.is_regular_file()) continue;
        auto path = entry.path();
        std::string ext = path.extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
        if (ext == ".jpg" || ext == ".jpeg" || ext == ".png" || ext == ".bmp") {
            Image img = LoadImage(path.string().c_str());
            if (img.data != nullptr) {
                resizeAndUpload(img);
                UnloadImage(img);
            }
        }
    }
}

void drawBackground() {
    if (selectedBackground == 0) {
        ClearBackground(RAYWHITE);
    } else if (selectedBackground > 0) {
        DrawTexture(backgroundTextures[selectedBackground - 1], 0, 0, WHITE);
    }
}

void unloadBackgroundTextures() {
    for (const auto& texture : backgroundTextures) {
        UnloadTexture(texture);
    }
}