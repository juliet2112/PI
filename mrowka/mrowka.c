#include "mrowka.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** allocateBoard(){
    srand(time(NULL));
    int **board = malloc(size * sizeof(int*));

    for(int i = 0; i < size; i++){
        board[i] = malloc(size * sizeof(int));
    }

    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            board[i][j] = rand()%8 + 1;
        }
    }
    return board;

}


int** allocateVisited(pair pos){
    int **visited = malloc(size * sizeof(int*));

    for(int i = 0; i < size; i++){
        visited[i] = malloc(size * sizeof(int));
    }

    for(int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            visited[i][j] = 0;
        }
    }
    visited[pos.x][pos.y] = 1;
    return visited;
}

void freeBoard(int** board){
    if(board) {
        free(board[0]);
        free(board);
    }
}

void displayBoard(Board board){
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf(" %d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
    printf("\n");
}

void makeMove(Board board, pair* pos, pair* kier){
    switch(board[pos->x][pos->y]){
        case 1:
            board[pos->x][pos->y] = 7;
            pos->x = (kier->x + pos->x) % size;
            pos->y = (kier->y + pos->y) % size;
        break;
        
        case 2:
            board[pos->x][pos->y] = 4;
            *kier = wprawo(*kier);
        break;

        case 3:
            board[pos->x][pos->y] = 2;
            *kier = wlewo(*kier);
            break;

        case 4:
            board[pos->x][pos->y] = 6;
            pair newp = wprawo(*kier);
            pos->x = (newp.x + pos->x)%size;
            pos->y = (newp.y + pos->y)%size;
            break;

        case 5:
            board[pos->x][pos->y] = 3;
            pair newl = wlewo(*kier);
            pos->x = (newl.x + pos->x)%size;
            pos->y = (newl.y + pos->y)%size;
            break;

        case 6:
            board[pos->x][pos->y] = 5;
            pos->x = (pos->x - kier->x)%size;
            pos->y = (pos->y - kier->y)%size;
            break;

        case 7:
            board[pos->x][pos->y] = 8;
            kier->x = -kier->x;
            kier->y = -kier->y;
            break;

        case 8:
            board[pos->x][pos->y] = 1;
            break;
    }

}

pair wprawo (pair kier){
    pair newp;
    if (kier.x == 0 && kier.y == 1){
        newp.x = 1;
        newp.y = 0;
    }
    else if (kier.x == 1 && kier.y == 0){
        newp.x = 0;
        newp.y = -1;
    }
    else if (kier.x == 0 && kier.y == -1){
        newp.x = -1;
        newp.y = 0;
    }
    else if (kier.x == -1 && kier.y == 0){
        newp.x = 0;
        newp.y = 1;
    }
    return newp;
}

pair wlewo(pair kier){
    pair newl;
    if (kier.x == 0 && kier.y == 1){
        newl.x = -1;
        newl.y = 0;
    }
    else if (kier.x == -1 && kier.y == 0){
        newl.x = 0;
        newl.y = -1;
    }
    else if (kier.x == 0 && kier.y == -1){
        newl.x = 1;
        newl.y = 0;
    }
    else if (kier.x == 1 && kier.y == 0){
        newl.x = 0;
        newl.y = 1;
    }
    return newl;
}