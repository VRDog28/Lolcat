#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

int main() {
    // Initialize random seed
    srand((unsigned int)time(NULL));

    // Random start RGB
    int r1 = rand() % 256;
    int g1 = rand() % 256;
    int b1 = rand() % 256;

    // Random end RGB
    int r2 = rand() % 256;
    int g2 = rand() % 256;
    int b2 = rand() % 256;

    // Enable ANSI escape sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    char line[4096];

    while (fgets(line, sizeof(line), stdin)) {
        int len = (int)strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        for (int i = 0; i < len; i++) {
            char c = line[i];
            double t = (len == 1) ? 0.0 : (double)i / (len - 1);

            // Linear interpolation for RGB
            int r = (int)(r1 + t * (r2 - r1) + 0.5);
            int g = (int)(g1 + t * (g2 - g1) + 0.5);
            int b = (int)(b1 + t * (b2 - b1) + 0.5);

            // 24-bit ANSI escape
            printf("\x1b[38;2;%d;%d;%dm%c\x1b[0m", r, g, b, c);
        }
        printf("\n");
    }

    return 0;
}
