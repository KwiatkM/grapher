#ifndef INOUT
#define INOUT

#include <stdio.h>

typedef struct {
double right;
double down;
} wierzcholek_t;

// inicjalizajca konteneru na graf
wierzcholek_t * kontenerInit (int x, int y);

// generowanie losowych wartości krawędzi
int gen_graf(wierzcholek_t * graf, int x, int y, double waga_od, double waga_do, double szansa);

// wczytanie wierzchołka z pliku
int wczytaj_graf (wierzcholek_t * graf, int x, int y, FILE * in);


// ( do testów ) wypisuje wagi krawędzi zapisane w strukturze 
void wypisz_graf(wierzcholek_t * graf, int x, int y);

//zapis grafu do pliku 
int zapiszGraf (wierzcholek_t * graf, int x, int y, FILE * out);








#endif