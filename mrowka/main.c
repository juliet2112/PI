#include "mrowka.h"
#include <stdio.h>

int main(){
    pair kier, pos;
    int t = 0;
    int kroki = 0;
    pos.x = 26;
    pos.y = 26;
    kier.x = 0;
    kier.y = 1;
    Board board = allocateBoard();
    Board visited = allocateVisited(pos);
    displayBoard(board);
    printf("Ile krokow ma wykonać mrowka?");
    scanf("%d", &kroki);

    while (t < kroki){
        makeMove(board,&pos,&kier);
        t += 1;
        visited[pos.x][pos.y] = 1;
    }

    displayBoard(board);
    displayBoard(visited);

    freeBoard(board);
    return 0;
}