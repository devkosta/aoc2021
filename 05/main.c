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
int linesSize = 0;

void swap(int *a, int *b) {
    int tem = *a;
    *a = *b;
    *b = tem;
}

int main(int argc, char *argv[]) {
    assert(argc == 2 && "Must Provide One Argument => input.txt path");
    printf("Input File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    while (fscanf(file, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2) == 4) {
        struct line curLine = {x1, y1, x2, y2};
        lines[linesSize++] = curLine;
    }

    // Problem 01
    {
        int count = 0;

        for (int i = 0; i < linesSize; ++i) {
            struct line curLine = lines[i];

            if (curLine.x1 != curLine.x2 && curLine.y1 != curLine.y2) {
                continue;
            }

            if (curLine.x1 > curLine.x2) swap(&curLine.x1, &curLine.x2);
            if (curLine.y1 > curLine.y2) swap(&curLine.y1, &curLine.y2);

            for (int x = curLine.x1; x <= curLine.x2; ++x) {
                for (int y = curLine.y1; y <= curLine.y2; ++y) {
                    if (board[x][y] == 1) count++;
                    board[x][y]++;
                }
            }
        }

        printf("Result 01: %d\n", count);
    }

    return 0;
}