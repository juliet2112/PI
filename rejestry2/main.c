#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main() {
    Node *list = NULL;
    Node *current = NULL;
    rekord buf;
    int choice;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Wczytaj dane z pliku\n");
        printf("2. Zapisz dane do pliku\n");
        printf("3. Dodaj rekord\n");
        printf("4. Wyświetl pierwszy rekord\n");
        printf("5. Wyświetl następny rekord\n");
        printf("6. Edytuj bieżący rekord\n");
        printf("7. Usuń bieżący rekord\n");
        printf("0. Wyjście\n");
        printf("Wybierz opcję: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                list = loadFromFile(list);
                printf("Dane wczytane.\n");
                break;
            case 2:
                saveToFile(list);
                printf("Dane zapisane.\n");
                break;
            case 3:
                printf("Podaj ID (szesnastkowo): ");
                scanf("%x", &buf.id);
                getchar();
                printf("Podaj nazwę: ");
                fgets(buf.name, sizeof(buf.name), stdin);
                buf.name[strcspn(buf.name, "\n")] = '\0';
                printf("Podaj rok: ");
                scanf("%d", &buf.year);
                printf("Rodzaj oferty (0-Sprzedaż, 1-Wypożyczenie, 2-Wizyta): ");
                scanf("%d", (int*)&buf.type);
                printf("Podaj cenę: ");
                scanf("%f", &buf.price);
                list = append(list, &buf);
                break;
            case 4:
                current = list;
                printFirst(list);
                break;
            case 5:
                current = printNext(current);
                break;
            case 6:
                if (current) editRecord(current->data);
                else printf("Brak wybranego rekordu.\n");
                break;
            case 7:
                if (current) {
                    list = deleteNode(list, current);
                    current = list;
                }
                break;
        }
    } while (choice != 0);

    freeList(list);
    return 0;
}
