#include "warcaby.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
        Board board;
        pair from, to;
        to.x = -1;
        to.y = -1;
        initializeBoard(board);
        displayBoard(board,to);

        srand(time(NULL));
        int turn = 0;

        while(1){
                if (turn == 0){
                        if(!canMove(board,0)){
                                printf("Wygrales!!!\n");
                                break;
                        }
                        int validMove = 0;
                        while(!validMove){
                                from.x = rand()%SIZE;
                                from.y = rand()%SIZE;
                                int direction = (rand()%2)? 1 : -1;
                                if(board[from.x][from.y] != 1){
                                        continue;
                                }
                                if (from.x + 2 * direction >= 0 && from.x + 2 * direction < SIZE && from.y + 2 >= 0 && from.y + 2 < SIZE && board[from.x + direction][from.y + 1] == 2 && board[from.x + 2 * direction][from.y + 2] == EMPTY){
                                        to.x = from.x + 2*direction;
                                        to.y = from.y + 2;
                                }
                                else{
                                        to.x = from.x + direction;
                                        to.y = from.y + ((rand()%2) ? 1: -1);
                                }

                                if(to.x >= 0 && to.x < SIZE && to.y >= 0 && to.y < SIZE){
                                        validMove = makeMove(board,from,to);
                                }
                        }
                }


                else{
                    if(!canMove(board, 1)){
                            printf("Brak mozliwych ruchow. Przegrales :(( \n");
                            break;
                    }

                    printf("Podaj wspolrzedne(x1 y1 x2 y2): ");
                    scanf("%d %d %d %d", &from.x, &from.y, &to.x, &to.y);
                    if(board[from.x][from.y] == 2){
                            if(!makeMove(board,from,to)){
                                    printf("Nieprwidlowy ruch\n");
                                    continue;
                            }
                    }
            }

            displayBoard(board, to);
            turn = 1-turn;
    }
    return 0;
}

