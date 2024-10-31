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
    geradores.emplace_back(this);
    geradorThread = std::thread([this]() {
        clock_t inicio = clock();
        while (this->executando) {
            if (!desbloqueado) continue;
            this->clocksDesdeUltimoCiclo = clock() - inicio;
            if (this->clocksDesdeUltimoCiclo < this->clocksPorCiclo) continue;
            inicio = clock();
            sem_wait(this->moedasSemaforo);
            *this->moedas += this->moedasPorCiclo;
            sem_post(this->moedasSemaforo);
        }
    });
}

bool GeradorDeMoedas::desbloquear() {
    if (*moedas >= custo) {
        sem_wait(moedasSemaforo);
        *moedas -= custo;
        sem_post(moedasSemaforo);
        desbloqueado = true;
        return true;
    }
    return false;;
}
