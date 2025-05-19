#ifndef REJESTRY_H
#define REJESTRY_H
#include <stdio.h>

#define file_name "dane.bin"

enum types {
    sprzedaz,
    wypozyczenie,
    wizyta
};

typedef struct{
    int id;
    char name[255];
    int year;
    enum types type;
    float price;
} rekord;

void moveForward(FILE *file, int ile);
void moveBack(FILE *file, int ile);
void newRecord(FILE *file);
void findAndEdit(FILE *file, int edit);
void showRecord(rekord *r);
void work();

#endif