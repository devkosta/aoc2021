#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1024

struct inst {
    int valid;
    char binVal[12];
};
struct inst bin[N];
int binSize = 0;

int binToDecimal(char binStr[12]) {
    int decimal = 0;

    for (int i = 0; i < 12; ++i) {
        if (binStr[i] == '1') {
            decimal |= 1 << (11 - i);
        }
    }

    return decimal;
}

int findCommonBit(int side) {
    for (int i = 0; i < binSize; ++i) {
        bin[i].valid = 1;
    }

    int valid = binSize, i = 0;

    while (valid > 1) {
        int ones = 0;

        for (int k = 0; k < binSize; ++k) {
            if (bin[k].valid && bin[k].binVal[i] == '1') {
                ones++;
            }
        }

        int commonBit = side ? ones >= valid / 2 : ones < valid / 2;

        for (int k = 0; k < binSize; ++k) {
            if (((bin[k].binVal[i] == '1') != commonBit) && bin[k].valid) {
                bin[k].valid = 0;
                valid--;
            }
        }

        i++;
    }

    char *res = "";
    res = malloc(sizeof(char) * 12);

    for (int i = 0; i < binSize; ++i) {
        if (bin[i].valid) {
            strcpy(res, bin[i].binVal);
        }
    }

    return binToDecimal(res);
}

int main(int argc, char *argv[]) {
    assert(argc == 2 && "Must Provide One Argument => input.txt path");
    printf("Input File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");
    char str[12] = "";

    while (fscanf(file, "%s", str) == 1) {
        bin[binSize].valid = 1;
        strcpy(bin[binSize++].binVal, str);
    }

    int ones[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < binSize; ++i) {
        for (int k = 0; k < 12; ++k) {
            int num = bin[i].binVal[k];

            if (num == '1') {
                ones[k]++;
            }
        }
    }

    // Problem 01
    {
        int gammaRate = 0, epsilonRate = 0;

        for (int i = 0; i < 12; ++i) {
            if (ones[i] > binSize / 2) {
                gammaRate |= 1 << (11 - i);
            } else {
                epsilonRate |= 1 << (11 - i);
            }
        }

        printf("Result 01: %d\n", gammaRate * epsilonRate);
    }

    // Problem 02
    {
        int oxygenRate = findCommonBit(1);
        int scrubberRate = findCommonBit(0);

        printf("Result 02: %d\n", oxygenRate * scrubberRate);
    }

    fclose(file);

    return 0;
}