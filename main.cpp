#include <iostream>
#include <raylib.h>

#include "game_objects/ovni/Ovni.h"
#include "game_objects/player/Player.h"

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(1280, 800, "Space Invaders");

    const auto player = new Player(LoadTexture("../assets/player1.png"), {1280 / 2, 800 - 100}, {0, 0, 64, 64});

    new Ovni(LoadTexture("../assets/ovni.png"), {1280 / 2, 0}, {0, 0, 64, 64});

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(WHITE);

        Sprite::drawAll();

        if (IsKeyDown(KEY_LEFT)) {
            player->moveLeft();
        }
        if (IsKeyDown(KEY_RIGHT)) {
            player->moveRight();
        }
        if (IsKeyPressed(KEY_SPACE)) {
            player->shoot();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
