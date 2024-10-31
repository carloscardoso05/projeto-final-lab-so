#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <semaphore.h>
#include <vector>

#include "raygui.h"
#include "configuration/Configuration.cpp"
#include "game_objects/worker/Worker.h"

int resources = 0;
sem_t resourceSemaphore;

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(windowWidth, windowHeight, "Clicker");

    sem_init(&resourceSemaphore, 0, 1);

    std::vector<Worker *> workers;
    workers.push_back(new Worker(50, &resources, 18, 20, &resourceSemaphore));
    workers.push_back(new Worker(50 * 4, &resources, 25, 15, &resourceSemaphore));
    workers.push_back(new Worker(50 * pow(4, 2), &resources, 32, 10, &resourceSemaphore));
    workers.push_back(new Worker(50 * pow(4, 3), &resources, 45, 5, &resourceSemaphore));
    workers.push_back(new Worker(50 * pow(4, 4), &resources, 60, 1, &resourceSemaphore));

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (GuiButton((Rectangle){350, 200, 100, 50}, "Gerar") || IsKeyPressed(KEY_SPACE)) {
            sem_wait(&resourceSemaphore);
            resources += 1;
            sem_post(&resourceSemaphore);
        }

        for (int i = 0; i < workers.size(); i++) {
            if (const auto worker = workers[i]; worker->unlocked) {
                float progress;
                progress = static_cast<float>(worker->elapsedTimeSinceLastGen % worker->timerInClocks);
                GuiProgressBar((Rectangle){350, static_cast<float>(200 + 100 * (i + 1)), 150, 100}, nullptr, nullptr,
                               &progress, 0.0f, static_cast<float>(worker->timerInClocks));
            } else {
                if (GuiButton((Rectangle){350, static_cast<float>(200 + 100 * (i + 1)), 150, 100},
                              TextFormat(
                                  "Desbloquear %d\nCusto: %d moedas\nTempo: %d segundos\nGera: %d moedas", i + 1,
                                  worker->cost,
                                  worker->timerInClocks / CLOCKS_PER_SEC,
                                  worker->generateResourcesPerTime
                              ))) {
                    worker->unlock();
                }
            }
        }

        DrawText("Clicker Game", 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Moedas: %d", resources), 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    Worker::stopAll();
    sem_destroy(&resourceSemaphore);
    CloseWindow();
    return 0;
}
