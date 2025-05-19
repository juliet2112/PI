#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <string.h>
#include "statystyk2.h"

int main(int argc, char *argv[]){
    int ile_n = 0;
    int ile_s = 0;
    double *liczby = calloc(MAX_WAR, sizeof(double));
    char **slowa = (char**)calloc(MAX_WAR, sizeof(char*));
    for (int i = 0; i < MAX_WAR; i++) {
        slowa[i] = (char *)calloc(MAX_LEN, sizeof(char));
    }

    for (int i = 1; i < argc; i++){
        rozpoznaj_typ(argv[i],liczby,slowa,&ile_n,&ile_s);
    }

    liczby = realloc(liczby, ile_n * sizeof(double));
    slowa = realloc(slowa, ile_s * sizeof(char*));
    for (int i = 0; i < ile_s; i++) {
        slowa[i] = realloc(slowa[i], strlen(slowa[i]) + 1);
    
    }
    printf("Dla liczb: ");
    for (int i = 0; i < ile_n; i++) {
        printf("%.2f, ", liczby[i]);
    }
    printf("\n");

    printf("Suma: %.2f\n", sum(liczby,ile_n)); 
    printf("Mediana: %.2f\n", median(liczby, ile_n));
    printf("Srednia: %.2f\n", avrg(liczby,ile_n));
    printf("Minimum: %.2f\n", minn(liczby, ile_n)); 
    printf("Maximum: %.2f\n", maxx(liczby, ile_n)); 

    printf("Pominięte: ");
    for (int i = 0; i < ile_s; i++) {
        printf("%s", slowa[i]);
        if (i < ile_s - 1) {
            printf(", ");
        }
    }
    printf("\n");

    for (int i = 0; i < ile_s; i++) {
        free(slowa[i]);
    }
    free(slowa);
    free(liczby);

    koniec(0);
}