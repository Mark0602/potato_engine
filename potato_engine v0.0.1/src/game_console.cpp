#include "game_console.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstdio>
#include <iostream>
#include <string>

namespace {

void report_console_error(const wchar_t* operation) {
    const DWORD error = GetLastError();
    const std::wstring message = std::wstring(operation) +
        L" failed (Windows error " + std::to_wstring(error) + L").";
    MessageBoxW(nullptr, message.c_str(), L"Potato Engine console error",
                MB_OK | MB_ICONERROR);
}

void reconnect_standard_streams() {
    FILE* stream = nullptr;
    freopen_s(&stream, "CONOUT$", "w", stdout);
    freopen_s(&stream, "CONOUT$", "w", stderr);
    freopen_s(&stream, "CONIN$", "r", stdin);

    std::ios::sync_with_stdio(true);
    std::cin.clear();
    std::cout.clear();
    std::cerr.clear();
}

} // namespace

namespace game_console {

bool is_console_visible() {
    const HWND console = GetConsoleWindow();
    return console && IsWindowVisible(console) != 0;
}

bool show_console() {
    HWND console = GetConsoleWindow();
    if (!console) {
        if (!AllocConsole()) {
            report_console_error(L"AllocConsole");
            return false;
        }
        console = GetConsoleWindow();
    }
    if (!console) {
        SetLastError(ERROR_INVALID_WINDOW_HANDLE);
        report_console_error(L"GetConsoleWindow");
        return false;
    }

    reconnect_standard_streams();
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleTitleW(L"Potato Engine debug console");

    ShowWindow(console, SW_RESTORE);
    SetWindowPos(console, HWND_TOP, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW | SWP_NOACTIVATE);
    std::cout << "Potato Engine debug console opened. "
                 "F1 or grave/0 hides it.\n";
    std::cout.flush();
    return true;
}

void hide_console() {
    if (const HWND console = GetConsoleWindow()) {
        ShowWindow(console, SW_HIDE);
    }
}

void toggle_console() {
    if (is_console_visible()) hide_console();
    else show_console();
}

bool handle_event(const SDL_Event& event) {
    if (event.type != SDL_EVENT_KEY_DOWN || event.key.repeat) return false;
    if (event.key.scancode != SDL_SCANCODE_F1 &&
        event.key.scancode != SDL_SCANCODE_GRAVE) return false;
    toggle_console();
    return true;
}

bool is_supported() { return true; }

} // namespace game_console

#else

namespace game_console {
bool is_console_visible() { return false; }
bool show_console() { return false; }
void hide_console() {}
void toggle_console() {}
bool handle_event(const SDL_Event&) { return false; }
bool is_supported() { return false; }
} // namespace game_console

#endif
