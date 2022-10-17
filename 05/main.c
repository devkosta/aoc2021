#include <assert.h>
#include <stdio.h>
#include <string.h>

#define N 1000
#define LINES 500

struct line {
    int x1;
    int y1;
    int x2;
    int y2;
};
int board[N][N] = {0};
struct line lines[LINES];
int lineSize = 0;

int main(int argc, char *argv[]) {
    assert(argc == 2 && "Must Provide One Argument => input.txt path");
    printf("Input File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    while (fscanf(file, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4) {
        struct line curLine = {x1, y1, x2, y2};
        lines[lineSize++] = curLine;
    }

    for (int i = 0; i < lineSize; ++i) {
        printf("%d,%d -> %d,%d\n", lines[i].x1, lines[i].y1, lines[i].x2, lines[i].y2);
    }

    return 0;
}