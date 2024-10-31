#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <semaphore.h>
#include <vector>

#include "raygui.h"
#include "configuration/Configuration.cpp"
#include "game_objects/worker/GeradorDeMoedas.h"

int moedas = 0;
sem_t moedasSemaforo;

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(windowWidth, windowHeight, "Clicker");

    sem_init(&moedasSemaforo, 0, 1);

    std::vector<GeradorDeMoedas *> geradores;
    geradores.push_back(new GeradorDeMoedas(50, &moedas, 18, 20, &moedasSemaforo));
    geradores.push_back(new GeradorDeMoedas(50 * 4, &moedas, 25, 15, &moedasSemaforo));
    geradores.push_back(new GeradorDeMoedas(static_cast<int>(50 * pow(4, 2)), &moedas, 32, 10, &moedasSemaforo));
    geradores.push_back(new GeradorDeMoedas(static_cast<int>(50 * pow(4, 3)), &moedas, 45, 5, &moedasSemaforo));
    geradores.push_back(new GeradorDeMoedas(static_cast<int>(50 * pow(4, 4)), &moedas, 60, 1, &moedasSemaforo));

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (GuiButton((Rectangle){350, 200, 100, 50}, "Gerar") || IsKeyPressed(KEY_SPACE)) {
            sem_wait(&moedasSemaforo);
            moedas += 1;
            sem_post(&moedasSemaforo);
        }

        for (int i = 0; i < geradores.size(); i++) {
            if (const auto gerador = geradores[i]; gerador->desbloqueado) {
                float progress;
                progress = static_cast<float>(gerador->clocksDesdeUltimoCiclo % gerador->clocksPorCiclo);
                GuiProgressBar((Rectangle){350, static_cast<float>(200 + 100 * (i + 1)), 150, 100}, nullptr, nullptr,
                               &progress, 0.0f, static_cast<float>(gerador->clocksPorCiclo));
            } else {
                if (GuiButton((Rectangle){350, static_cast<float>(200 + 100 * (i + 1)), 150, 100},
                              TextFormat(
                                  "Desbloquear %d\nCusto: %d moedas\nTempo: %d segundos\nGera: %d moedas", i + 1,
                                  gerador->custo,
                                  gerador->clocksPorCiclo / CLOCKS_PER_SEC,
                                  gerador->moedasPorCiclo
                              ))) {
                    gerador->desbloquear();
                }
            }
        }

        DrawText("Clicker Game", 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Moedas: %d", moedas), 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    GeradorDeMoedas::pararTodos();
    sem_destroy(&moedasSemaforo);
    CloseWindow();
    return 0;
}
