#ifndef INOUT
#define INOUT

#include <stdio.h>

typedef struct e {
double right;
double down;
} wierzcholek_t;

int krawedzDodaj (int x, int y, int nr_w_1, int nr_w_2, double wartosc);

int wagiWypisz (int x, int y, int nr_w, char * out);






#endif