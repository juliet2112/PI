#ifndef WARCABY_H
#define WARCABY_H

#define SIZE 10

#define EMPTY 0
#define WHITE_PAWN 1
#define BLACK_PAWN 2

typedef struct {
    int x;
    int y;
} pair;

typedef int Board[SIZE][SIZE];

void displayBoard(Board board, pair last);
void initializeBoard(Board board);
int canMove(Board board, int player);
int makeMove(Board board, pair from, pair to);
void capturePiece(Board board, pair from, pair to);

#endif
