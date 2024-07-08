//
// Created by Sakura on 06.07.2024.
//

#include "ProcReader.h"
#include "ProcGetter.h"

ProcReader::ProcReader(HANDLE hProc, const char* procName, const char *modName) {
    this->procName = procName;
    this->hProc = hProc;
    this->moduleBase = getModuleBaseAddress(modName);
}

bool ProcReader::readMemoryOffset(unsigned char *array, const int offset, const int size) {
    if (!isRunning()) {
        // Try to get the process handle again
        hProc = ProcGetter::getProcHandle(procName);
        if (hProc == nullptr) {
            return false;
        }
    }

    ReadProcessMemory(hProc, (LPCVOID) (moduleBase + offset), array, size, nullptr);
}

bool ProcReader::readMemoryOffset(int* value,int offset) {
    if (!isRunning()) {
        // Try to get the process handle again
        hProc = ProcGetter::getProcHandle(procName);
        if (hProc == nullptr) {
            return false;
        }
    }

    ReadProcessMemory(hProc, (LPCVOID) (moduleBase + offset), &value, sizeof(*value), nullptr);
    return value != nullptr;
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
