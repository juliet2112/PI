#include <stdio.h>
#include <stdlib.h>
#include "rejestry.h"
#include <string.h>


void moveForward(FILE *file, int ile){
    fseek(file, ile *sizeof(rekord), SEEK_CUR);
}

void moveBack(FILE *file, int ile){
    fseek(file, -ile*sizeof(rekord), SEEK_CUR);
}

void findAndEdit(FILE *file, int edit) {
    int x;
    rekord temp;
    long positions[100];
    int count = 0;

    fseek(file, 0, SEEK_SET);
    printf("Po czym chcesz wyszukiwać? (1 - id, 2 - fragment nazwy, 3 - tańsze niż ...): ");
    scanf("%d", &x);
    getchar();

    switch (x) {
        case 1: {
            int idn;
            printf("Podaj id (szesnastkowo): ");
            scanf("%x", &idn);
            fseek(file, 0, SEEK_SET);
            while (fread(&temp, sizeof(rekord), 1, file)) {
                if (temp.id == idn) {
                    positions[count++] = ftell(file) - sizeof(rekord);
                    showRecord(&temp);
                }
            }
            break;
        }
        case 2: {
            char nazwa[254];
            printf("Podaj fragment nazwy: ");
            fgets(nazwa, sizeof(nazwa), stdin);
            nazwa[strcspn(nazwa, "\n")] = '\0';
            fseek(file, 0, SEEK_SET);
            while (fread(&temp, sizeof(rekord), 1, file)) {
                if (strstr(temp.name, nazwa)) {
                    positions[count++] = ftell(file) - sizeof(rekord);
                    showRecord(&temp);
                }
            }
            break;
        }
        case 3: {
            float cena;
            printf("Podaj maksymalną cenę: ");
            scanf("%f", &cena);
            fseek(file, 0, SEEK_SET);
            while (fread(&temp, sizeof(rekord), 1, file)) {
                if (temp.price <= cena) {
                    positions[count++] = ftell(file) - sizeof(rekord);
                    showRecord(&temp);
                }
            }
            break;
        }
        default:
            printf("Nieprawidłowa opcja.\n");
            return;
    }

    if (count == 0) {
        printf("Nie znaleziono pasujących rekordów.\n");
        return;
    }

    if (!edit) return;

    int choice;
    if (count == 1) {
        choice = 0;
    } else {
        printf("Wybierz numer rekordu do edycji (1 - %d): ", count);
        scanf("%d", &choice);
        choice--;
        if (choice < 0 || choice >= count) {
            printf("Nieprawidłowy wybór.\n");
            return;
        }
    }

    fseek(file, positions[choice], SEEK_SET);
    fread(&temp, sizeof(rekord), 1, file);

    printf("Obecna cena: %.2f PLN\n", temp.price);
    printf("Nowa cena: ");
    scanf("%f", &temp.price);

    fseek(file, positions[choice], SEEK_SET);
    fwrite(&temp, sizeof(rekord), 1, file);
    printf("Cena zaktualizowana.\n");
}

void newRecord(FILE *file){
    rekord new;
    printf("Podaj id (liczna całkowita w postaci szesnastkowej): ");
    scanf("%x", &new.id);
    getchar();

    char temp[264];
    printf("Podaj nazwę: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';

    strcpy(new.name,temp);


    printf("Podaj rok powstania (wartość całkowita ze znakiem): ");
    scanf("%d", &new.year);
    printf("Podaj rodzaj oferty (1 - sprzedaż, 2 - wypożyczenie, 3 - wizyta): ");
    scanf("%d", (int*)&new.type);
    printf("Podaj cenę: ");
    scanf("%f", &new.price);

    fwrite(&new, sizeof(rekord), 1, file);
}


void showRecord(rekord *r) {
    printf("\n--- Rekord ---\n");
    printf("ID: %X\n", r->id);
    printf("Nazwa: %s\n", r->name);
    printf("Rok: %d\n", r->year);
    printf("Rodzaj oferty: ");
    switch (r->type) {
        case sprzedaz: printf("Sprzedaż\n"); break;
        case wypozyczenie: printf("Wypożyczenie\n"); break;
        case wizyta: printf("Wizyta\n"); break;
        default: printf("Nieznany\n");
    }
    printf("Cena: %.2f PLN\n", r->price);
}

void work(){
    FILE *file = fopen(file_name, "r+b");
    if (file == NULL){
        printf("Nie można otworzyć pliku");
        return;
    }

    int x, ile;
    rekord rek;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Następny rekord\n");
        printf("2. Poprzedni rekord\n");
        printf("3. Szukaj rekordu\n");
        printf("4. Dodaj rekord\n");
        printf("5. Zmień cenę\n");
        printf("6. Wyświetl bieżący rekord\n");
        printf("0. Wyjście\n");
        printf("Opcja: ");
        scanf("%d", &x);
        getchar();

        switch (x)
        {
        case 1:
            printf("O ile rekordów? ");
            scanf("%d",&ile);
            moveForward(file, ile);
            break;

        case 2:
            printf("O ile rekordów? ");
            scanf("%d",&ile);
            moveBack(file, ile);
            break;

        case 3:
            findAndEdit(file,0);
            break;

        case 4:
            newRecord(file);
            break;

        case 5:
            findAndEdit(file, 1);
            break;
    
        case 6:
            fread(&rek, sizeof(rekord), 1, file);
            showRecord(&rek);
            break;
        }

    } while (x != 0);

    fclose(file);
}