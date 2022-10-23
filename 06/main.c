#include <assert.h>
#include <stdio.h>
#include <string.h>

#define N 300

typedef unsigned long long int u64;

int input[N] = {0};
int inputSize = 0;

u64 solve(u64 fishes[], int numDays) {
    for (int i = 0; i < numDays; ++i) {
        fishes[9] = fishes[0];
        memmove(fishes, &fishes[1], 9 * sizeof(u64));
        fishes[6] += fishes[8];
    }

    u64 result = 0;
    for (int i = 0; i < 9; ++i) {
        result += fishes[i];
    }

    return result;
}

int main(int argc, char *argv[]) {
    assert(argc == 2 && "Must Provide One Argument => input.txt path");
    printf("Input File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");
    int number = 0;

    while (fscanf(file, "%d,", &number) == 1) {
        input[inputSize++] = number;
    }

    // Problem 01
    {
        u64 fishes[10];
        memset(fishes, 0, 10 * sizeof(u64));

        for (int i = 0; i < inputSize; ++i) {
            fishes[input[i]]++;
        }

        u64 res = solve(fishes, 80);

        printf("Result 01: %llu\n", res);
    }

    // Problem 02
    {
        u64 fishes[10];
        memset(fishes, 0, 10 * sizeof(u64));

        for (int i = 0; i < inputSize; ++i) {
            fishes[input[i]]++;
        }

        u64 res = solve(fishes, 256);

        printf("Result 02: %llu\n", res);
    }

    return 0;
}