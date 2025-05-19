#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statystyk2.h"

double sum(double *A, int n){
    double suma = 0;
    for (int i = 0; i < n; i++){
        suma += A[i];
    }
    return suma;
}

double avrg(double *A, int n){
    double suma = 0;
    for (int i = 0; i < n; i++){
        suma += A[i];
    }
    return suma/n;
}

double median(double *A, int n){
    double *copy = malloc(n * sizeof(double));
    double med;
    for (int i = 0; i < n; i++) {
        copy[i] = A[i];
    }

    if (n%2 == 1){
        med = quickselect(copy,0,n-1,n/2+1);
    }
    else{
        med = quickselect(copy,0,n-1,n/2+1) + quickselect(copy,0,n-1,n/2);
        med /= 2.0;
    }
    free(copy);
    return med;
}

double quickselect(double *A, int p, int r, int x){
    while (p < r){
        int q = partition(A,p,r);
        if (q == x){
            return A[x];
        }
        else if(x < q){
            r = q-1;
        }
        else{
            p = q+1;
        }
    }
    return A[x];
}

int partition(double *A, int p, int r){
    int x = (p+r)/2;
    swap(A,r,x);
    int i = p-1;
    for (int j = p; j < r; j++){
        if (A[j] < A[r]){
            i++;
            swap(A,j,i);
        }
    }
    swap(A,i+1,r);
    return i+1;
}

int swap(double *A, int a, int b){
    double temp = A[b];
    A[b] = A[a];
    A[a] = temp;
}

double minn(double *A, int n){
    double mini = A[0];
    for (int i = 1; i < n; i++){
        if (A[i] < mini){
            mini = A[i];
        }
    }
    return mini;
}

double maxx(double *A, int n){
    double maxi = A[0];
    for (int i = 1; i < n; i++){
        if (A[i] > maxi){
            maxi = A[i];
        }
    }
    return maxi;
}

void rozpoznaj_typ (char *t, double *liczby, char **slowa, int *ile_n, int *ile_s){
    char *endptr;

    errno = 0;
    double d = strtod(t, &endptr);
    if (errno == 0 && *endptr == '\0'){
        liczby[*ile_n] = (double)d;
        (*ile_n)++;
        return;
    }

    errno = 0;
    long l = strtol(t, &endptr, 0);
    if (errno == 0 && *endptr == '\0') {
        liczby[*ile_n] = (double)l;
        (*ile_n)++;
        return;
    }

    strcpy(slowa[*ile_s],t);
    (*ile_s)++;
}

__declspec(noreturn) void koniec(int state) {
      puts("To jest już koniec!");
        exit(state); 
} 