#ifndef INOUT
#define INOUT

#include <stdio.h>  //for FILE

typedef struct e {
double right;
double down;
} wierzcholek_t;

int x, y;

void createGraph(wierzcholek_t **graf, int wymiar_x, int wymiar_y, double waga_od, double waga_do, double szansa);

void saveGraph(wierzcholek_t **graf, int wymiar_x, int wymiar_y, FILE * file_out_graph);

#endif