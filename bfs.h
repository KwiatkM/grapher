#ifndef BFS
#define BFS

#include "inout.h"       //for wierzcholek_t structure

typedef struct f {
int nr_wierz;
struct f * next;
} kolejka_t;

int x, y;
char ** tab_odw;
kolejka_t * koniec;
kolejka_t * poczatek;

void bfsTabInit (int wymiar_x, int wymiar_y);    

void kolejkaInit (void);

int kolejkaDodaj (kolejka_t ** first_elem, kolejka_t ** last_elem, int nr_wierz);

int kolejkaZdejmij (kolejka_t ** first_elem, kolejka_t ** last_elem);

int bfs (wierzcholek_t **graf, int wymiar_x, int wymiar_y, char **tab_odw);

#endif