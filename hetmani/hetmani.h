#include <stdio.h>
#include <stdbool.h>

#ifndef HETMANI_H
#define HETMANI_H

#define SIZE 8

bool isSafe(int **board, int row, int col);
bool placeQueens(int **board, int row);
void printBoard(int **board);
#endif