#include "maszyna.h"

int main() {
    inicjalizuj_pamiec();
    wyswietl_pamiec();

    while (true) {
        krok();
    }

    return 0;
}
