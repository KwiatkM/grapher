#ifndef BFS
#define BFS

#include "inout.h"       //for wierzcholek_t structure

typedef struct f {
int nr_wierz;
struct f * next;
} kolejka_t;

int x, y, nr;
extern char *tab_odw;
kolejka_t * koniec;
kolejka_t * poczatek;

static int bfsTabInit (int wymiar_x, int wymiar_y);    

static void kolejkaInit (kolejka_t ** first_elem, kolejka_t ** last_elem);

static int kolejkaDodaj (kolejka_t ** first_elem, kolejka_t ** last_elem, int nr_wierz);

static int kolejkaZdejmij (kolejka_t ** first_elem, kolejka_t ** last_elem);

int bfs (wierzcholek_t **graf, int wymiar_x, int wymiar_y);

#endif