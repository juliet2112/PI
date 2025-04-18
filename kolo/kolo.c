#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "kolo.h"

const char* texts[MAX_TEXTS] = {
    "SCHODY DO NIEBA",
    "WARIANTY MAŁOLATA",
    "PACHNIESZ BRZOSKWINIA",
    "LOBBY INSTRUKTORSKIE",
    "HOKEJKA",
    "PRAWY HEINRICH",
    "KANT HAKOWY",
    "ZEMSTA WACLAWA",
    "AMERICAN BEAUTY",
    "INDIANSKIE LATO",
    "FESTIWAL GRANITU",
    "PRAWI WRZESNIACY",
    "FILAR MOTYLI",
    "ROMBOIDALNA PLYTA",
    "STUDZIENKA MNICHOWA",
    "GRAN WIDEL",
    "NAJSZCZERSZY USMIECH POKOLENIA",
    "GALERIA GANKOWA",
    "KULUAR KURTYKI",
    "KOMIN POKUTNIKÓW"
};

player* inicjalizuj(int number){
    player *board = malloc(number * sizeof(player));
    for (int i = 0; i < number;i++){
        char nazwa[50];
        printf("Podaj nazwę gracza %d:", i+1);
        fgets(nazwa, sizeof(nazwa), stdin);

        nazwa[strcspn(nazwa, "\n")] = '\0';
        
        board[i].name = malloc(strlen(nazwa) + 1 * sizeof(char));

        strcpy(board[i].name, nazwa);
        board[i].score = 0;
    }
    return board;
}

haslo *wylosuj_haslo(int* used) {
    int indeks;
    srand(time(NULL));
    do
    {
        indeks = rand() % MAX_TEXTS;
    } while (used[indeks] == 1);
    used[indeks] = 1;

    haslo* wynik = malloc(strlen(texts[indeks]) * sizeof(haslo) + 1);
    
    for (int i = 0; texts[indeks][i] != '\0'; i++){
        wynik[i].znak = texts[indeks][i];
        if(texts[indeks][i] == ' '){
            wynik[i].guess = 1;
        }
        else{
            wynik[i].guess = 0;
        }
    }
    return wynik;
}

void print(haslo* tekst, player* board, int number_of_players){
    printf("\nHasło: ");
    for (int i = 0; tekst[i].znak != '\0'; i++){
        if(tekst[i].guess == 1){
            printf("%c", tekst[i].znak);
        }
        else{
            printf("_");
        }
    }
    printf("\n");
    for (int i = 0; i < number_of_players; i++){
        printf("Wynik gracza numer %s to: %d\n",board[i].name,board[i].score);
    }
}

int check_if_guessed(haslo* tekst){
    for (int i = 0; tekst[i].znak != '\0'; i++){
        if(tekst[i].guess == 0){
            return 0;
        }
    }
    return 1;
}

int check_if_in_haslo(haslo* tekst, player* board, int player_number, int num_of_players, char znak){
    int czy = 0;
    int znak_lower = tolower((unsigned char)znak);
    int znak_upper = toupper((unsigned char)znak);
    for (int i = 0; tekst[i].znak != '\0'; i++){
       if(tekst[i].guess == 0 && (tekst[i].znak == znak_lower || tekst[i].znak == znak_upper)){
            board[player_number].score +=1;
            tekst[i].guess = 1; 
            czy = 1;
       }
    }
    return(czy);
}

void play(player* board, int num_of_players){
    int used[MAX_TEXTS];
    int player_number = 0;
    for(int i = 0; i < MAX_TEXTS; i++){
        used[i]= 0;
    }
    for(int i = 0; i < MAX_TEXTS; i++){
        haslo *tekst = wylosuj_haslo(used);
        while(check_if_guessed(tekst) == 0){
            char znak;
            print(tekst,board,num_of_players);
            printf("Teraz kolej gracza %s, podaj literę: ", board[player_number].name);
            scanf("%c", &znak);
            while (getchar() != '\n');
            if(check_if_in_haslo(tekst, board,player_number, num_of_players, znak)==0){
                player_number = (player_number+1)%num_of_players;
            }
        }
        printf("Odgadnięte hasło to: %s \n", tekst);
    }
    printf("Oto ostateczne wyniki: \n");
    for (int i = 0; i < num_of_players; i++){
        printf("Wynik gracza numer %s to: %d\n",board[i].name,board[i].score);
    }

}