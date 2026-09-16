#pragma once

namespace calculator {

int getTerminalWidth();
void clearScreen();
void enableUtf8Console();
void printSpaces(int spaceCount);
int countTextWidth(const char* text);

}
