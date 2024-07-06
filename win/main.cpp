#include <windows.h>
#include <iostream>
#include "ProcGetter.h"
#include "ProcReader.h"
#include "DeathCounter.h"
#include "overlay.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
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
    if (process_handle == nullptr) {
        std::cerr << "Failed to get process handle." << std::endl;
        return -1;
    }

    auto proc_reader = ProcReader(process_handle, module_name);

    // Start overlay
    std::cout << "Starting overlay..." << std::endl;

    auto overlay = Overlay(hInstance);
    overlay.show();

    std::cout << "Overlay started." << std::endl;
    auto death_counter = DeathCounter(&proc_reader, [&overlay](int death_count) {
        std::cout << "Deaths: " << death_count << std::endl;
        overlay.update(death_count);
    });


    std::thread death_counter_thread([&death_counter]() {
        while (true) {
            death_counter.tick();
        }
    });

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    CloseHandle(process_handle);
    return 0;
}
