#ifndef DIJ
#define DIJ

#include <stdio.h>

typedef struct e {
int nr_wierz;
struct e * next;
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