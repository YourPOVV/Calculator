#include "terminal.h"
#include "theme.h"
#include <cstdlib>
#include <cstdio>

#ifdef _WIN32
#include <windows.h>
#endif

namespace calculator {

int getTerminalWidth() {
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleHandle == INVALID_HANDLE_VALUE) {
        return 80;
    }

    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    if (!GetConsoleScreenBufferInfo(consoleHandle, &screenInfo)) {
        return 80;
    }

    return screenInfo.srWindow.Right - screenInfo.srWindow.Left + 1;
#else
    const char* columnCountText = std::getenv("COLUMNS");
    if (columnCountText != nullptr) {
        const int terminalWidth = std::atoi(columnCountText);
        if (terminalWidth > 0) {
            return terminalWidth;
        }
    }
    return 80;
#endif
}

void clearScreen() {
    std::fputs(CLEAR_SCREEN, stdout);
    std::fflush(stdout);
}

void enableUtf8Console() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleHandle == INVALID_HANDLE_VALUE) {
        return;
    }

    DWORD consoleMode = 0;
    if (!GetConsoleMode(consoleHandle, &consoleMode)) {
        return;
    }

    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(consoleHandle, consoleMode);
#endif
}

void printSpaces(int spaceCount) {
    for (int spaceIndex = 0; spaceIndex < spaceCount; ++spaceIndex) {
        std::putchar(' ');
    }
}

int countTextWidth(const char* text) {
    int characterCount = 0;
    for (const unsigned char* character = reinterpret_cast<const unsigned char*>(text);
         *character;
         ++character) {
        if ((*character & 0xC0) != 0x80) {
            ++characterCount;
        }
    }
    return characterCount;
}

}
