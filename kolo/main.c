#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kolo.h"

int main(){
    int num_of_players;
    printf("Podaj liczbę graczy: ");
    scanf("%d", &num_of_players);
    while (getchar() != '\n'); 
    Board table = inicjalizuj(num_of_players);
    play(table, num_of_players);
    free(table);
    return 0;
}