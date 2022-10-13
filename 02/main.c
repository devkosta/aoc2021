#include <assert.h>
#include <stdio.h>
#include <string.h>

#define N 2048

struct inst {
    int num;
    char dir[10];
};

struct inst instArr[N];
int instSize = 0;

int main(int argc, char *argv[]) {
    assert(argc == 2 && "Must Provide One Argument => input.txt path");
    printf("Input File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");
    int number = 0;
    char str[10] = "";

    while (fscanf(file, "%s", str) == 1 && fscanf(file, "%d", &number) == 1) {
        instArr[instSize].num = number;
        strcpy(instArr[instSize++].dir, str);
    }

    // Problem 01
    {
        int forward = 0, down = 0;
        for (int i = 0; i < N; ++i) {
            if (strcmp(instArr[i].dir, "forward") == 0) {
                forward += instArr[i].num;
            } else if (strcmp(instArr[i].dir, "down") == 0) {
                down += instArr[i].num;
            } else {
                down -= instArr[i].num;
            }
        }

        printf("Result 01: %d\n", forward * down);
    }

    // Problem 02
    {
        int aim = 0, forward = 0, down = 0;
        for (int i = 0; i < N; ++i) {
            if (strcmp(instArr[i].dir, "forward") == 0) {
                forward += instArr[i].num;
                down += aim * instArr[i].num;
            } else if (strcmp(instArr[i].dir, "down") == 0) {
                aim += instArr[i].num;
            } else {
                aim -= instArr[i].num;
            }
        }

        printf("Result 02: %d\n", forward * down);
    }

    fclose(file);

    return 0;
}