#include <assert.h>
#include <stdio.h>

#define N 2048
unsigned int numbers[N];
int numbersSize = 0;

int main(int argc, char *argv[]) {
    assert(argc == 2 && "Must Provide One Argument => input.txt path");
    printf("Input File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");
    int number = 0;

    while (fscanf(file, "%d", &number) == 1) {
        numbers[numbersSize++] = number;
    }

    // Problem 01
    {
        int res = 0;
        for (int i = 1; i < N; ++i) {
            if (numbers[i] > numbers[i - 1]) {
                res++;
            }
        }

        printf("Result 01: %d\n", res);
    }

    // Problem 02
    {
        int res = 0;
        for (int i = 1; i < N - 2; ++i) {
            int A = numbers[i - 1] + numbers[i] + numbers[i + 1];
            int B = numbers[i] + numbers[i + 1] + numbers[i + 2];

            if (B > A) {
                res++;
            }
        }
        
        printf("Result 02: %d\n", res);
    }

    fclose(file);

    return 0;
}