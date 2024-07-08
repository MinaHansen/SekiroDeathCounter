//
// Created by Sakura on 06.07.2024.
//


#include "DeathCounter.h"

#include <utility>
#include <iostream>

DeathCounter::DeathCounter(ProcReader *proc_reader, std::function<void(int)> death_callback) {
    this->proc_reader = proc_reader;
    this->death_callback = std::move(death_callback);
}

// Called in a loop
int DeathCounter::tick() {
    if (!proc_reader->isRunning()) {
        std::cerr << "Process is not running." << std::endl;
        return -1;
    }

    int current_health = 0;
    if (proc_reader->readMemoryOffset(&current_health, health_memory_offset)) {
        std::cerr << "Failed to read memory." << std::endl;
        return -1;
    }

    if (current_health <= 0 && last_health > 0) {
        death_count++;
        death_callback(death_count);
    }
    last_health = current_health;
    return 0;
}
