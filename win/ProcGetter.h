//
// Created by Sakura on 06.07.2024.
//

#ifndef SEKIRODEATHCOUNTER_PROCGETTER_H
#define SEKIRODEATHCOUNTER_PROCGETTER_H

#include <windows.h>
#include <tlhelp32.h>

class ProcGetter {
public:
    static HANDLE getProcHandle(const char* procName);
    static DWORD getProcId(const char *name);
};


#endif //SEKIRODEATHCOUNTER_PROCGETTER_H
