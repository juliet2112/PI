#include "warcaby.h"
#include <stdio.h>

void displayBoard(Board board, pair last) {
        for(int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++){
                        if(last.x == i && last.y == j){
                               printf("[%d]", board[i][j]);
                        }
                        else{
                                printf(" %d ", board[i][j]);
                        }
                }
                printf("\n");
        }
        printf("\n");
        printf("\n");
        printf("\n");
}

void initializeBoard(Board board) {
        for (int i = 0; i < SIZE; i++){
                for(int j = 0; j < SIZE; j++){
                        if (i < 4 && (i+j)%2 == 1){
                                board[i][j] = BLACK_PAWN;
                        }
                        else if (i > 5 && (i+j)%2 == 1){
                                board[i][j] = WHITE_PAWN;
                        }
                        else {
                                board[i][j] = EMPTY;
                        }
                }
        }
}

int canMove(Board board, int player) {
    int piece = (player == 1) ? WHITE_PAWN : BLACK_PAWN;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == piece) {
                if (board[i+1][j] == EMPTY) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int makeMove(Board board, pair from, pair to){
    if(board[to.x][to.y] != EMPTY) return 0;

    if((to.x-from.x == 2 || to.x-from.x == -2) && (to.y-from.y == 2 || to.y - from.y == -2) ) {
            capturePiece(board,from,to);
    }

    board[to.x][to.y] = board[from.x][from.y];
    board[from.x][from.y] = EMPTY;

    promotePawn(board,to);

    return 1;
}

void capturePiece(Board board, pair from, pair to){
    pair mid;
    mid.x = (from.x + to.x)/2;
    mid.y = (from.y + to.y)/2;
    board[mid.x][mid.y] = EMPTY;
}

