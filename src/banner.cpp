#include "banner.h"
#include "terminal.h"
#include "theme.h"
#include <cstdio>

namespace {

const char* TITLE = "yourpov.dev";
const char* SUBTITLE = "Calculator";

}

namespace calculator {

void showBanner() {
    enableUtf8Console();

    int terminalWidth = getTerminalWidth();
    if (terminalWidth <= 0) {
        terminalWidth = 80;
    }

    const int titleWidth = countTextWidth(TITLE);
    const int subtitleWidth = countTextWidth(SUBTITLE);
    const int contentWidth = (titleWidth > subtitleWidth ? titleWidth : subtitleWidth) + 4;
    const int boxWidth = contentWidth + 2;

    const int margin = (terminalWidth - boxWidth) / 2;
    const int titlePad = (contentWidth - titleWidth) / 2;
    const int subtitlePad = (contentWidth - subtitleWidth) / 2;

    std::printf("\n");
    printSpaces(margin);
    std::printf("%s┌", DEFAULT);
    for (int lineIndex = 0; lineIndex < boxWidth - 2; ++lineIndex) {
        std::fputs("─", stdout);
    }
    std::printf("┐%s\n", RESET);

    printSpaces(margin);
    std::printf("%s│%s", DEFAULT, RESET);
    printSpaces(titlePad);
    std::printf("%s%s%s", SECONDARY, TITLE, RESET);
    printSpaces(contentWidth - titleWidth - titlePad);
    std::printf("%s│%s\n", DEFAULT, RESET);

    printSpaces(margin);
    std::printf("%s│ %s", DEFAULT, RESET);
    for (int lineIndex = 0; lineIndex < contentWidth - 2; ++lineIndex) {
        std::fputs("─", stdout);
    }
    std::printf("%s │%s\n", DEFAULT, RESET);

    printSpaces(margin);
    std::printf("%s│%s", DEFAULT, RESET);
    printSpaces(subtitlePad);
    std::printf("%s%s%s", ACCENT, SUBTITLE, RESET);
    printSpaces(contentWidth - subtitleWidth - subtitlePad);
    std::printf("%s│%s\n", DEFAULT, RESET);

    printSpaces(margin);
    std::printf("%s└", DEFAULT);
    for (int lineIndex = 0; lineIndex < boxWidth - 2; ++lineIndex) {
        std::fputs("─", stdout);
    }
    std::printf("┘%s\n\n", RESET);
}

}
