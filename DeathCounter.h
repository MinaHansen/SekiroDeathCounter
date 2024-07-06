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

    int death_count = 0;
    int last_health = 0;

public:
    DeathCounter(ProcReader* proc_reader, std::function<void(int)> death_callback);
    int tick();
};


#endif //SEKIRODEATHCOUNTER_DEATHCOUNTER_H
