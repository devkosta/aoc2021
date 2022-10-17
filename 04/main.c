#include <assert.h>
#include <stdio.h>
#include <string.h>

#define N 500

struct boardNum {
    int marked;
    int num;
};
struct boardNum boards[N][5];
int numbers[100];
int numbersSize = 0;

void printBoard(int rowNum) {
    for (int r = (rowNum - 4); r <= rowNum; ++r) {
        for (int c = 0; c < 5; ++c) {
            printf("%d ", boards[r][c].marked);
        }
        printf("\n");
    }
}

int checkBoard(int rowNum) {
    // Check Rows
    for (int r = (rowNum - 4); r <= rowNum; ++r) {
        int won = 1;
        for (int c = 0; c < 5; ++c) {
            if (!boards[r][c].marked) {
                won = 0;
                break;
            }
        }

        if (won) return 1;
    }

    // Check Cols
    for (int c = 0; c < 5; ++c) {
        int won = 1;
        for (int r = (rowNum - 4); r <= rowNum; ++r) {
            if (!boards[r][c].marked) {
                won = 0;
                break;
            }
        }

        if (won) return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    assert(argc == 2 && "Must Provide One Argument => input.txt path");
    printf("Input File: %s\n", argv[1]);

    FILE *file = fopen(argv[1], "r");
    char buff[300];
    char *curLine;
    int in, offset, cols, rows = 0;

    while (fscanf(file, "%[^\n] ", buff) != EOF) {
        cols = 0;
        curLine = buff;
        if (strchr(curLine, ',') != NULL) {
            while (sscanf(curLine, "%d,%n", &in, &offset) == 1) {
                numbers[numbersSize++] = in;
                curLine += offset;
            }
        } else {
            while (sscanf(curLine, "%d%n", &in, &offset) == 1) {
                struct boardNum val = {0, in};
                boards[rows][cols] = val;

                cols++;
                curLine += offset;
            }
            rows++;
        }
    }

    // Problem 01
    {
        for (int n = 0; n < numbersSize; ++n) {
            int drawnNum = numbers[n], won = 0;

            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < 5; ++c) {
                    if (boards[r][c].num == drawnNum) {
                        boards[r][c].marked = 1;
                    }
                }
                if (r != 0 && (r + 1) % 5 == 0) {
                    if (checkBoard(r)) {
                        int unmarkedSum = 0;

                        // Sum of unmarked numbers.
                        for (int i = (r - 4); i <= r; ++i) {
                            for (int k = 0; k < 5; ++k) {
                                if (!boards[i][k].marked) {
                                    unmarkedSum += boards[i][k].num;
                                }
                            }
                        }

                        printf("Result 01: %d\n", unmarkedSum * drawnNum);
                        won = 1;
                    }
                }
            }
            if (won) break;
        }
    }

    // Reset marked values.
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < 5; ++c) {
            boards[r][c].marked = 0;
        }
    }

    // Problem 02
    {
        int numRows = rows / 5, finishedBoards[100], won = 0;
        memset(finishedBoards, 0, 100 * sizeof(int));

        for (int n = 0; n < numbersSize; ++n) {
            int drawnNum = numbers[n];

            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < 5; ++c) {
                    if (boards[r][c].num == drawnNum) {
                        boards[r][c].marked = 1;
                    }
                }

                if (r != 0 && (r + 1) % 5 == 0) {
                    int curBoardNum = ((r + 1) / 5) - 1;

                    if (!finishedBoards[curBoardNum] && checkBoard(r)) {
                        finishedBoards[curBoardNum] = 1;
                        int unmarkedSum = 0;

                        // Sum of unmarked numbers.
                        for (int i = (r - 4); i <= r; ++i) {
                            for (int k = 0; k < 5; ++k) {
                                if (!boards[i][k].marked) {
                                    unmarkedSum += boards[i][k].num;
                                }
                            }
                        }

                        won++;
                        if (won == numRows) {
                            printf("Result 02: %d\n", unmarkedSum * drawnNum);
                        }
                    }
                }
            }
            if (won == numRows) break;
        }
    }

    fclose(file);

    return 0;
}