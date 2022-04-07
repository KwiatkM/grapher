#ifndef INOUT
#define INOUT

#include <stdio.h>

typedef struct {
double right;
double down;
} wierzcholek_t;

// inicjalizajca konteneru na graf
wierzcholek_t * kontenerInit (int x, int y);

// wczytanie wierzchołka z pliku
int wczytaj_graf (wierzcholek_t * graf, int x, int y, FILE * in);

int wagiWypisz (int x, int y, int nr_w, char * out);

// funkcja do testowania
void wypisz_graf(wierzcholek_t * graf, int x, int y);

//zapis grafu do pliku 
int zapiszGraf (wierzcholek_t * graf, int x, int y, FILE * out);








#endif