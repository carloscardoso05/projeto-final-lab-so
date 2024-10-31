#ifndef WORKER_H
#define WORKER_H
#include <semaphore.h>
#include <thread>
#include <vector>


class GeradorDeMoedas {
    sem_t *moedasSemaforo;
    std::thread geradorThread;
public:
    static std::vector<GeradorDeMoedas*> geradores;
    static void pararTodos();

    GeradorDeMoedas(int custo, int *moedas, int moedasPorCiclo, int clocksPorCiclo, sem_t *moedasSemaforo);

    bool executando{true};
    bool desbloqueado{false};
    int custo{};
    int *moedas;
    int moedasPorCiclo{};
    clock_t clocksPorCiclo{};
    clock_t clocksDesdeUltimoCiclo{};

    bool desbloquear();
};


#endif
