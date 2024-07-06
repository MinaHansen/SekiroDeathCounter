//
// Created by Sakura on 06.07.2024.
//

#include "ProcReader.h"

ProcReader::ProcReader(HANDLE hProc, const char *modName) {
    this->hProc = hProc;
    this->moduleBase = getModuleBaseAddress(modName);
}

void ProcReader::readMemoryOffset(unsigned char *array, const int offset, const int size) {
    ReadProcessMemory(hProc, (LPCVOID) (moduleBase + offset), array, size, nullptr);
}

int ProcReader::readMemoryOffset(int offset) {
    int buffer;
    ReadProcessMemory(hProc, (LPCVOID) (moduleBase + offset), &buffer, sizeof(buffer), nullptr);
    return buffer;
}

uintptr_t ProcReader::getModuleBaseAddress(const char *modName) {
    uintptr_t moduleBaseAddress = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, GetProcessId(hProc));
    if (hSnap != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry)) {
            do {
                if (!strcmp(modEntry.szModule, modName)) {
                    moduleBaseAddress = (uintptr_t) modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return moduleBaseAddress;
}

bool ProcReader::isRunning() {
    DWORD exitCode;
    GetExitCodeProcess(hProc, &exitCode);
    return exitCode == STILL_ACTIVE;
}
