#include <stdio.h>
#include "hetmani.h"

bool isSafe(int **board, int row, int col){
    for(int i = 0; i < row; i++){
        if (board[i][col] == 1){
            return false;
        }
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j < SIZE; i--, j++) {
        if (board[i][j] == 1) {
            return false;
        }
    }

    return true;
}

    
bool placeQueens(int **board, int row){
    if (row == SIZE){
        return true;
    }
    for(int i = 0; i < SIZE; i++){
        if (isSafe(board, row, i) == true){
            board[row][i] = 1;
            if(placeQueens(board,row+1)==true){
                return true;
            }
            board[row][i] = 0
        }
    }
    return false
}

void printBoard(int **board){
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++){
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
}