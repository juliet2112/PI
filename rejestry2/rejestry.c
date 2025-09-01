#include "rejestry.h"
#include <stdio.h>

void showRecord(rekord *r) {
    printf("\n--- Rekord ---\n");
    printf("ID: %X\n", r->id);
    printf("Nazwa: %s\n", r->name);
    printf("Rok: %d\n", r->year);
    printf("Rodzaj oferty: ");
    switch (r->type) {
        case SPRZEDAZ: printf("Sprzedaż\n"); break;
        case WYPOZYCZENIE: printf("Wypożyczenie\n"); break;
        case WIZYTA: printf("Wizyta\n"); break;
        default: printf("Nieznany\n");
    }
    printf("Cena: %.2f PLN\n", r->price);
}
