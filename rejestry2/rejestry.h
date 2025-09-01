#ifndef REJESTRY_H
#define REJESTRY_H

#include <stdio.h>

#define FILE_NAME "dane.bin"

enum types {
    SPRZEDAZ,
    WYPOZYCZENIE,
    WIZYTA
};

typedef struct {
    int id;
    char name[255];
    int year;
    enum types type;
    float price;
} rekord;

void showRecord(rekord *r);

#endif