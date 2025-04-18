#ifndef MROWKA_H
#define MROWKA_H

#define size 51

typedef struct {
    int x;
    int y;
} pair;


typedef int** Board;
int** allocateBoard();
int** allocateVisited(pair pos);
void freeBoard(int** board);
void displayBoard(Board board);
void makeMove (Board board, pair* pos, pair* kier);
pair wprawo (pair kier);
pair wlewo (pair kier);
#endif