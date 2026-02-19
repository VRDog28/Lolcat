#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int r1, g1, b1; 
    int r2, g2, b2;
} Gradient;

int main(int argc, char *argv[]) {
    Gradient presets[] = {
        {255, 0, 0, 255, 255, 0},       
        {0, 255, 0, 0, 255, 255},       
        {0, 0, 255, 255, 0, 255},       
        {255, 128, 0, 128, 0, 255}      
    };
    int numpresets = sizeof(presets)/sizeof(presets[0]);
    srand((unsigned int)time(NULL));
    int presetindex;
    if (argc > 1) {
        presetindex = atoi(argv[1]) - 1; 
        if (presetindex < 0 || presetindex >= numpresets) {
            presetindex = rand() % numpresets; 
        }
    } else {
        presetindex = rand() % numpresets; 
    }
    int r1 = presets[presetindex].r1;
    int g1 = presets[presetindex].g1;
    int b1 = presets[presetindex].b1;

    int r2 = presets[presetindex].r2;
    int g2 = presets[presetindex].g2;
    int b2 = presets[presetindex].b2;
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

            int r = (int)(r1 + t * (r2 - r1) + 0.5);
            int g = (int)(g1 + t * (g2 - g1) + 0.5);
            int b = (int)(b1 + t * (b2 - b1) + 0.5);

            printf("\x1b[38;2;%d;%d;%dm%c\x1b[0m", r, g, b, c);
        }
        printf("\n");
    }

    return 0;
}
