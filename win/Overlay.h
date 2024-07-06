//
// Created by Sakura on 06.07.2024.
//

#ifndef SEKIRODEATHCOUNTER_OVERLAY_H
#define SEKIRODEATHCOUNTER_OVERLAY_H


#include <minwindef.h>
#include <windef.h>

class Overlay {
private:
    inline static Overlay* instance = nullptr;
    HINSTANCE hInstance = nullptr;
    HWND hWnd = nullptr;
    HFONT hFont = nullptr;

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    int death_count = 0;

public:
    explicit Overlay(HINSTANCE hInstance);
    ~Overlay();
    int show();
    int hide();
    int update(int deaths);
};


#endif //SEKIRODEATHCOUNTER_OVERLAY_H
