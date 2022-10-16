#include <assert.h>
#include <stdio.h>
#include <string.h>

#define N 500

struct boardNum {
    int marked;
    int num;
};
struct boardNum boards[N][5];
int boardSize = 0;
int numbers[100];
int numbersSize = 0;

int main(int argc, char *argv[]) {
    assert(argc == 2 && "Must Provide One Argument => input.txt path");
    printf("Input File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");
    char buff[300];
    char *curLine;
    int in, offset, col, row = 0;

    while (fscanf(file, "%[^\n] ", buff) != EOF) {
        col = 0;
        curLine = buff;
        if (strchr(curLine, ',') != NULL) {
            while (sscanf(curLine, "%d,%n", &in, &offset) == 1) {
                numbers[numbersSize++] = in;
                curLine += offset;
            }
        } else {
            while (sscanf(curLine, "%d%n", &in, &offset) == 1) {
                struct boardNum val = {0, in};
                boards[row][col] = val;

                col++;
                curLine += offset;
            }
            row++;
        }
    }

    fclose(file);

    return 0;
}