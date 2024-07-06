//
// Created by Sakura on 06.07.2024.
//

#ifndef SEKIRODEATHCOUNTER_DEATHCOUNTER_H
#define SEKIRODEATHCOUNTER_DEATHCOUNTER_H

#include <thread>
#include <functional>
#include "ProcReader.h"

class DeathCounter {
private:
    const int health_memory_offset = 0x3D8BB44;

    ProcReader* proc_reader;
    std::function<void(int)> death_callback;
    std::thread* thread{};

    volatile bool is_running = false;
    int death_count = 0;

    void run();

public:
    DeathCounter(ProcReader* proc_reader, std::function<void(int)> death_callback);
    void start();
    void stop();
};


#endif //SEKIRODEATHCOUNTER_DEATHCOUNTER_H
