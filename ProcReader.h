//
// Created by Sakura on 06.07.2024.
//

#ifndef SEKIRODEATHCOUNTER_PROCREADER_H
#define SEKIRODEATHCOUNTER_PROCREADER_H

#include <windows.h>
#include <tlhelp32.h>
#include <vector>

class ProcReader {
private:
    HANDLE hProc;
    uintptr_t moduleBase;

    uintptr_t getModuleBaseAddress(const char* modName);
public:
    explicit ProcReader(HANDLE hProc, const char* modName);

    bool isRunning();
    int readMemoryOffset(int offset);
    void readMemoryOffset(unsigned char* array, int offset, int size);
};


#endif //SEKIRODEATHCOUNTER_PROCREADER_H
