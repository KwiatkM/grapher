#ifndef INOUT
#define INOUT

#include <stdio.h>

typedef struct {
double right;
double down;
} wierzcholek_t;

// inicjalizajca konteneru na graf
wierzcholek_t * kontenerInit (int x, int y);

int krawedzDodaj (int x, int y, int nr_w_1, int nr_w_2, double wartosc);

int wagiWypisz (int x, int y, int nr_w, char * out);

// funkcja do testowania
void wypisz_graf(wierzcholek_t * graf, int x, int y);

//zapis grafu do pliku 
int zapiszGraf (wierzcholek_t * graf, int x, int y, FILE * out);








#endif