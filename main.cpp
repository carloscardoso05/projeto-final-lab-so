#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include <semaphore.h>
#include <vector>

#include "raygui.h"
#include "configuration/Configuration.cpp"
#include "game_objects/worker/GeradorDeMoedas.h"

int moedas = 0; // Quantidade de moedas do jogador
sem_t moedasSemaforo; // Semáforo para garantir que a variável moedas seja acessada de forma segura

int main() {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

    InitWindow(windowWidth, windowHeight, "Clicker");

    sem_init(&moedasSemaforo, 0, 1); // Inicializa o semáforo com 1, ou seja, ele está desbloqueado

    // Cria os geradores de moedas
    std::vector<GeradorDeMoedas *> geradores;
    geradores.push_back(new GeradorDeMoedas(50, &moedas, 18, 20, &moedasSemaforo));
    geradores.push_back(new GeradorDeMoedas(50 * 4, &moedas, 25, 15, &moedasSemaforo));
    geradores.push_back(new GeradorDeMoedas(static_cast<int>(50 * pow(4, 2)), &moedas, 32, 10, &moedasSemaforo));
    geradores.push_back(new GeradorDeMoedas(static_cast<int>(50 * pow(4, 3)), &moedas, 45, 5, &moedasSemaforo));
    geradores.push_back(new GeradorDeMoedas(static_cast<int>(50 * pow(4, 4)), &moedas, 60, 1, &moedasSemaforo));

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        // Botão para gerar moedas
        if (GuiButton((Rectangle){350, 200, 100, 50}, "Gerar") || IsKeyPressed(KEY_SPACE)) {
            sem_wait(&moedasSemaforo);
            moedas += 1;
            sem_post(&moedasSemaforo);
        }

        // Mostra os geradores de moedas
        for (int i = 0; i < geradores.size(); i++) {
            // Se o gerador está desbloqueado, mostra a barra de progresso
            if (const auto gerador = geradores[i]; gerador->desbloqueado) {
                float progress;
                // Calcula o progresso da barra de progresso
                progress = static_cast<float>(gerador->clocksDesdeInicioDoCiclo % gerador->clocksPorCiclo);
                GuiProgressBar((Rectangle){350, static_cast<float>(200 + 100 * (i + 1)), 150, 100}, nullptr, nullptr,
                               &progress, 0.0f, static_cast<float>(gerador->clocksPorCiclo));
            } else {
                // Se o gerador não está desbloqueado, mostra o botão para desbloquear
                if (GuiButton(
                        (Rectangle){350, static_cast<float>(200 + 100 * (i + 1)), 150, 100},
                        TextFormat(
                            "Desbloquear %d\nCusto: %d moedas\nTempo: %d segundos\nGera: %d moedas", i + 1,
                            gerador->custo,
                            gerador->clocksPorCiclo / CLOCKS_PER_SEC,
                            gerador->moedasPorCiclo
                        ))
                ) {
                    gerador->desbloquear();
                }
            }
        }

        DrawText("Clicker Game", 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Moedas: %d", moedas), 10, 40, 20, DARKGRAY); // Mostra a quantidade de moedas

        EndDrawing();
    }

    GeradorDeMoedas::pararTodos(); // Para todos os geradores
    sem_destroy(&moedasSemaforo); // Destrói o semáforo
    CloseWindow(); // Fecha a janela
    return 0;
}
