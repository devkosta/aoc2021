#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define N 1024

int crabs[N];
int crabsSize = 0;

void merge(int arr[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;

    int L[n1], M[n2];

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[p + i];
    }
    for (int k = 0; k < n2; ++k) {
        M[k] = arr[q + 1 + k];
    }

    int i = 0, c = 0, k = p;

    while (i < n1 && c < n2) {
        if (L[i] <= M[c]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[c];
            c++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (c < n2) {
        arr[k] = M[c];
        c++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    assert(argc == 2 && "Must Provide One Argument => input.txt path");
    printf("Input File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");
    int number = 0;

    while (fscanf(file, "%d,", &number) == 1) {
        crabs[crabsSize++] = number;
    }

    mergeSort(crabs, 0, crabsSize - 1);

    // Problem 01
    {
        int res = 0, mid = (crabsSize - 1) / 2;
        int median = crabs[mid];

        for (int i = 0; i < crabsSize; ++i) {
            res += abs(crabs[i] - median);
        }

        printf("Result 01: %d\n", res);
    }

    // Problem 02
    {
        int res = 0, mid = (crabsSize - 1) / 2;
        int median = crabs[mid];

        for (int i = 0; i < crabsSize; ++i) {
            res += abs(crabs[i] - median);
        }

        printf("Result 02: %d\n", res);
    }

    return 0;
}