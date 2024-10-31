#ifndef WORKER_H
#define WORKER_H
#include <semaphore.h>
#include <thread>
#include <vector>


class Worker {
    sem_t *resourceSemaphore;
    std::thread workerThread;
public:
    static std::vector<Worker*> workers;
    static void stopAll();

    Worker(int cost, int *resources, int generateResourcesPerTime, int timerInSeconds, sem_t *resourceSemaphore);

    bool running{true};
    bool unlocked{false};
    int cost{};
    int *resources;
    int generateResourcesPerTime{};
    clock_t timerInClocks{};
    clock_t elapsedTimeSinceLastGen{};

    bool unlock();
};


#endif
