#ifndef DIJ
#define DIJ

#include "inout.h"       //for wierzcholek_t structure

typedef struct h {
int nr_wierz;
struct h *next;
struct h *prev;
} pkolejka_t;

extern int *poprzednik;
extern double *odleglosc;
extern char *odwiedzono;

// inicjalizacja tablic poprzedników, odległości i odwiedzonych
static int dijTabInit (int wymiar_x, int wymiar_y);

// dodawanie wierzhcołków do kolejki priorytetowej
static int pKolejkaDodaj (pkolejka_t **kolejka, int nr_wierz);

// zdejmowanie wierzchołków z kolejki priorytetowej
static int pKolejkaZdejmij (pkolejka_t **kolejka);

// przesunięcie wierzchołka w kolejce priorytetowej
static int pKolejkaAktualizuj (pkolejka_t **kolejka, int nr_wierz);

// wypisanie kolejki (do testowania)
int pKolejkaWypisz (pkolejka_t *kolejka);

// algorytm dijkstry
int dijkstra (wierzcholek_t **graf, int wymiar_x, int wymiar_y, int w_start, int w_konc);

// wypisanie tablic (do testowania)
int wypiszTablice(int wymiar_x, int wymiar_y);

// wypisuje ścieżke między dwoma wierzchołakmi na podane wyjście
int wypisz_sciezke(FILE *out, int w_start, int w_konc);

#endif