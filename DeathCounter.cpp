//
// Created by Sakura on 06.07.2024.
//


#include "DeathCounter.h"

#include <utility>

DeathCounter::DeathCounter(ProcReader *proc_reader, std::function<void(int)> death_callback) {
    this->proc_reader = proc_reader;
    this->death_callback = std::move(death_callback);
}

void DeathCounter::start() {
    if (thread != nullptr) {
        return;
    }

    is_running = true;
    thread = new std::thread(&DeathCounter::run, this);
}

void DeathCounter::stop() {
    if (thread == nullptr) {
        return;
    }

    is_running = false;

    thread->join();
    delete thread;
    thread = nullptr;
}

void DeathCounter::run() {
    int last_health = 0;
    while (is_running) {
        int health = proc_reader->readMemoryOffset(health_memory_offset);
        if (health <= 0 && last_health > 0) {
            death_callback(++death_count);
        }
        last_health = health;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
