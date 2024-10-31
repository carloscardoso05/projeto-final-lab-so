#include "GeradorDeMoedas.h"
#include <semaphore.h>

std::vector<GeradorDeMoedas *> GeradorDeMoedas::geradores;

void GeradorDeMoedas::pararTodos() {
    for (const auto &gerador: geradores) {
        gerador->executando = false;
        gerador->geradorThread.join();
    }
}

GeradorDeMoedas::GeradorDeMoedas(const int custo, int *moedas, const int moedasPorCiclo, const int clocksPorCiclo,
                                 sem_t *moedasSemaforo) : moedasSemaforo(moedasSemaforo),
                                                          custo(custo),
                                                          moedas(moedas),
                                                          moedasPorCiclo(moedasPorCiclo),
                                                          clocksPorCiclo(clocksPorCiclo * CLOCKS_PER_SEC) {
    geradores.emplace_back(this); // Adiciona o gerador à lista de geradores
    // Inicia a thread do gerador
    geradorThread = std::thread([this]() {
        // Inicia o contador de clocks
        clock_t inicio = clock();
        // Loop principal do gerador
        while (this->executando) {
            // Se o gerador não está desbloqueado, pula para a próxima iteração
            if (!desbloqueado) continue;
            // Calcula a quantidade de clocks desde o início do ciclo
            this->clocksDesdeInicioDoCiclo = clock() - inicio;
            // Se a quantidade de clocks desde o início do ciclo for menor que a quantidade de clocks por ciclo, pula para a próxima iteração
            if (this->clocksDesdeInicioDoCiclo < this->clocksPorCiclo) continue;
            inicio = clock(); // Reinicia o contador de clocks
            sem_wait(this->moedasSemaforo); // Espera o semáforo
            *this->moedas += this->moedasPorCiclo; // Adiciona as moedas ao jogador
            sem_post(this->moedasSemaforo); // Libera o semáforo
        }
    });
}

bool GeradorDeMoedas::desbloquear() {
    // Se o jogador tiver moedas suficientes, desbloqueia o gerador
    if (*moedas >= custo) {
        sem_wait(moedasSemaforo);
        *moedas -= custo;
        sem_post(moedasSemaforo);
        desbloqueado = true;
        return true;
    }
    return false;;
}
