#include "maszyna.h"

symbole pamiec[PAMIEC_ROZMIAR];
int poz = 0;
stany stan = S0;

void inicjalizuj_pamiec() {
    for (int i = 0; i < PAMIEC_ROZMIAR; i++) {
        pamiec[i] = (i % 2 == 0) ? Z0 : Z1;
    }
}

void wyswietl_pamiec() {
    for (int i = 0; i < PAMIEC_ROZMIAR; i++) {
        if (i == poz) {
            printf("[%d]", pamiec[i]);
        } else {
            printf(" %d ", pamiec[i]);
        }
    }
    printf("\n");
}

void krok() {
    switch (stan) {
        case S0:
            if (pamiec[poz] == Z0) {
                pamiec[poz] = Z1;
                poz = (poz > 0) ? poz - 1 : 99;
                stan = S1;
            } else { 
                pamiec[poz] = Z0;
                stan = S0;
            }
            break;

        case S1:
            if (pamiec[poz] == Z0) {
                pamiec[poz] = Z1;
                poz = (poz < 99) ? poz + 1 : 0;
                stan = S0;
            } else {
                pamiec[poz] = Z0;
                printf("Maszyna zatrzymana na pozycji %d.\n", poz);
                return;
            }
            break;
    }

    printf("Stan: %d, Poz: %d\n", stan, poz);
    wyswietl_pamiec();
}
