#include <string>  
#include "raylib.h"
#include "globalFunc.hpp"
#include "background.hpp"
#include "globalSettings.hpp"

static int speedModifier = 1;

static const double MOVE_INTERVAL = 1.0 / 5.0;
static double lastMoveTime = 0.0;
static double currentTime;
static ScreenPosition PlayerPosition;
static bool debugMenuActive = false;

void input() {
    if (IsKeyDown(KEY_ESCAPE) || (IsKeyDown(KEY_C) && IsKeyDown(KEY_LEFT_CONTROL))) {
        globalShutoff = true;
        return;
    }
    if (IsKeyPressed(KEY_F1)) {
        debugMenuActive = !debugMenuActive;
    }
    if (IsKeyPressed(KEY_UP)) {
        speedModifier++;
    } else if (IsKeyPressed(KEY_DOWN)) {
        speedModifier--;
    }
}


void playerInput() {
    currentTime = GetTime();
    if (currentTime - lastMoveTime < MOVE_INTERVAL) {
        return;
    }

    if (IsKeyDown(KEY_W)) {
        PlayerPosition.y -= 5 * speedModifier;
    } else if (IsKeyDown(KEY_S)) {
        PlayerPosition.y += 5 * speedModifier;
    }

    if (IsKeyDown(KEY_D)) {
        PlayerPosition.x += 5 * speedModifier;
    } else if (IsKeyDown(KEY_A)) {
        PlayerPosition.x -= 5 * speedModifier;
    }

    lastMoveTime = currentTime;
}


void debugmenu() {
    if (debugMenuActive) {
        DrawText("Debug Menu", 10, 10, windowSize.x / 10, BLACK);
        DrawText("Player Position:", 10, 20, windowSize.x / 10, BLACK);
        DrawText(("(x:" + std::to_string(PlayerPosition.x) + ", y:" + std::to_string(PlayerPosition.y) + ")").c_str(), 10, 30, windowSize.x / 10, BLACK);
        DrawText(("Speed Modifier: " + std::to_string(speedModifier)).c_str(), 10, 40, windowSize.x / 10, BLACK);
    }
}


void draw() {
    drawBackground();
    //ClearBackground(RAYWHITE);
    DrawRectangle(PlayerPosition.x, PlayerPosition.y, 50, 50, RED);
    if (debugMenuActive) {
        DrawRectangle(PlayerPosition.x, PlayerPosition.y, 4, 4, BLACK);
    }
}


int main() {
    importAppSettings();
    InitWindow(windowSize.x, windowSize.y, "Visual Aid");
    loadBackgroundTextures();
    PlayerPosition.x = windowSize.x / 2;
    PlayerPosition.y = windowSize.y / 2;

    while (!WindowShouldClose() && IsWindowReady() && !globalShutoff) {
        input();
        playerInput();
        BeginDrawing();
        draw();
        debugmenu();
        EndDrawing();
    }

    unloadBackgroundTextures();
    CloseWindow();
    return 0;
}