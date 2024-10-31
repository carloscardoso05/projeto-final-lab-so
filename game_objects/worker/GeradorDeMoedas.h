#ifndef WORKER_H
#define WORKER_H
#include <semaphore.h>
#include <thread>
#include <vector>

// Classe que representa um gerador de moedas
class GeradorDeMoedas {
    sem_t *moedasSemaforo; // Semáforo para garantir que a variável moedas seja acessada de forma segura
    std::thread geradorThread; // Thread que executa o gerador
public:
    static std::vector<GeradorDeMoedas*> geradores; // Lista de geradores de moedas
    static void pararTodos(); // Para todos os geradores de moedas

    GeradorDeMoedas(int custo, int *moedas, int moedasPorCiclo, int clocksPorCiclo, sem_t *moedasSemaforo);

    bool executando{true}; // Indica se o gerador está executando
    bool desbloqueado{false}; // Indica se o gerador está desbloqueado
    int custo{}; // Custo para desbloquear o gerador
    int *moedas; // Ponteiro para a quantidade de moedas do jogador
    int moedasPorCiclo{}; // Quantidade de moedas geradas por ciclo
    clock_t clocksPorCiclo{}; // Quantidade de clocks por ciclo
    clock_t clocksDesdeInicioDoCiclo{}; // Quantidade de clocks desde o início do ciclo

    bool desbloquear(); // Desbloqueia o gerador se o jogador houver moedas suficientes
};


#endif
