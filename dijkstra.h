#ifndef DIJ
#define DIJ

#include <stdio.h>

typedef struct f {
int nr_wierz;
struct f * next;
} pkolejka_t;

int* poprzednik;
double* odleglosc;
char* odwiedzono;

int dijTabInit (int x, int y);

pkolejka_t * pKolejkaInit ( void );

int pKolejkaDodaj (int nr_wierz );

int pKolejkaZdejmij ( void );

int dijkstra ( int w_start );

#endif