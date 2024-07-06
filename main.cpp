#include <windows.h>
#include <iostream>
#include "ProcGetter.h"
#include "ProcReader.h"
#include "DeathCounter.h"

int main() {
    const char disclaimer[] = "###########################################################################\n"
                              "This program is not extensively tested and may not work as expected.\n"
                              "Source: https://github.com/SakuraKade/SekiroDeathCounter\n"
                              "License: GNU General Public License v3.0\n"
                              "This program is provided as is without any warranty. Use at your own risk.\n"
                              "###########################################################################";

    std::cout << disclaimer << std::endl << std::endl;

    const char process_name[] = "sekiro.exe";
    const char module_name[] = "sekiro.exe";

    HANDLE process_handle = ProcGetter::getProcHandle(process_name);
    auto proc_reader = ProcReader(process_handle, module_name);
    auto death_counter = DeathCounter(&proc_reader, [](int death_count) {
        std::cout << "Deaths: " << death_count << std::endl;
    });

    death_counter.start();
    std::cout << "Death counter started." << std::endl;

    // Wait forever until the user closes the program
    while (true) {
        Sleep(1000);
    }

    CloseHandle(process_handle);
    return 0;
}
