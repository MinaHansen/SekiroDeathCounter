//
// Created by Sakura on 06.07.2024.
//

#include "ProcGetter.h"

HANDLE ProcGetter::getProcHandle(const char *procName) {
    HANDLE hProc = NULL;
    hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcGetter::getProcId(procName));
    return hProc;
}

DWORD ProcGetter::getProcId(const char *name) {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);
        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!strcmp(procEntry.szExeFile, name)) {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}