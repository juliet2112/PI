#ifndef STATYSTYK2_H
#define STATYSTYK2_H
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>


#define MAX_WAR 100
#define MAX_LEN 254

double sum(double *A, int n);
double avrg(double *A, int n);
double median(double *A, int n);
double quickselect(double *A, int p, int r, int x);
int partition(double *A, int p, int r);
int swap(double *A, int a, int b);
double minn(double *A, int n);
double maxx(double *A, int n);
void rozpoznaj_typ (char *tekst, double*liczby, char **slowa, int *ile_n, int *ile_s);
__declspec(noreturn) void koniec(int stat);

#endif