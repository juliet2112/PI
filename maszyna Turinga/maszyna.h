#ifndef MASZYNA_H
#define MASZYNA_H

#include <stdio.h>
#include <stdbool.h>

typedef enum {
    S0, S1
} stany;

typedef enum {
    Z0, Z1
} symbole;

#define PAMIEC_ROZMIAR 100

extern symbole pamiec[PAMIEC_ROZMIAR];
extern int poz;
extern stany stan;

void inicjalizuj_pamiec();
void krok();
void wyswietl_pamiec();

#endif
