#include "Worker.h"
#include <semaphore.h>

std::vector<Worker *> Worker::workers;

void Worker::stopAll() {
    for (const auto &worker: workers) {
        worker->running = false;
        worker->workerThread.join();
    }
}

Worker::Worker(const int cost, int *resources, const int generateResourcesPerTime, const int timerInSeconds,
               sem_t *resourceSemaphore) : resourceSemaphore(resourceSemaphore),
                                           cost(cost),
                                           resources(resources),
                                           generateResourcesPerTime(generateResourcesPerTime),
                                           timerInClocks(timerInSeconds * CLOCKS_PER_SEC) {
    workers.emplace_back(this);
    workerThread = std::thread([this]() {
        clock_t start = clock();
        while (this->running) {
            if (!unlocked) continue;
            this->elapsedTimeSinceLastGen = clock() - start;
            if (this->elapsedTimeSinceLastGen < this->timerInClocks) continue;
            start = clock();
            sem_wait(this->resourceSemaphore);
            *this->resources += this->generateResourcesPerTime;
            sem_post(this->resourceSemaphore);
        }
    });
}

bool Worker::unlock() {
    if (*resources >= cost) {
        sem_wait(resourceSemaphore);
        *resources -= cost;
        sem_post(resourceSemaphore);
        unlocked = true;
        return true;
    }
    return false;;
}
