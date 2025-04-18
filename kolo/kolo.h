#ifndef KOLO_H
#define KOLO_H

#define MAX_PLAYERS 4
#define MAX_TEXTS 20

typedef struct{
    char* name;
    int score;
} player;

typedef player* Board;

typedef struct{
    char znak;
    int guess;
} haslo;

extern const char* texts[MAX_TEXTS];

player* inicjalizuj(int number);
haslo* wylosuj_haslo(int* used);
void print(haslo* tekst, player* board, int number_of_players);
int check_if_guessed(haslo* tekst);
int check_if_in_haslo(haslo* tekst, player* board, int player_number, int num_of_players, char znak);
void play(player* board, int num_of_players);
#endif
