//
// Created by Sakura on 06.07.2024.
//

#include <Windows.h>
#include <string>
#include "Overlay.h"

Overlay::Overlay(HINSTANCE hInstance) {
    this->instance = this;
    this->hInstance = hInstance;
    hFont = CreateFont(
            48, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
            DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_SWISS, "Arial"
            );
}

int Overlay::show() {
    const char CLASS_NAME[] = "SekiroDeathCounterOverlay";

    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = Overlay::WndProc;
    wc.hInstance = this->hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject(NULL_BRUSH);
    wc.lpszClassName = CLASS_NAME;

    RegisterClassEx(&wc);

    this->hWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST,
                                CLASS_NAME,
                                "Game Overlay",
                                WS_POPUP,
                                CW_USEDEFAULT, CW_USEDEFAULT, 300, 100,
                                nullptr, nullptr, this->hInstance, nullptr);

    SetLayeredWindowAttributes(this->hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(this->hWnd, SW_SHOW);
    return 0;
}

LRESULT Overlay::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // Clear the window
            RECT rect;
            GetClientRect(hWnd, &rect);
            HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(hdc, &rect, brush);
            DeleteObject(brush);

            // Draw text
            SetBkMode(hdc, TRANSPARENT);
            SetTextColor(hdc, RGB(255, 0, 0));

            auto oldFont = (HFONT) SelectObject(hdc, Overlay::instance->hFont);

            std::string text = "Deaths: " + std::to_string(Overlay::instance->death_count);
            TextOut(hdc, 10, 10, text.c_str(), (int)text.length());

            SelectObject(hdc, oldFont);
            EndPaint(hWnd, &ps);
        }
            break;
        case WM_DESTROY: {
            PostQuitMessage(0);
        }
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

int Overlay::hide() {
    ShowWindow(this->hWnd, SW_HIDE);
    return 0;
}

int Overlay::update(int deaths) {
    death_count = deaths;
    InvalidateRect(this->hWnd, nullptr, TRUE);
    UpdateWindow(this->hWnd);
    return 0;
}

Overlay::~Overlay() {
    DeleteObject(hFont);
    DestroyWindow(this->hWnd);
    UnregisterClass("SekiroDeathCounterOverlay", this->hInstance);
}
