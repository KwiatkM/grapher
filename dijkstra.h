#ifndef DIJ
#define DIJ


typedef struct f {
int nr_wierz;
struct f * next;
struct f * prev;
} pkolejka_t;

extern int * poprzednik;
extern double * odleglosc;
extern char * odwiedzono;

int dijTabInit (int x, int y);

int pKolejkaDodaj ( pkolejka_t ** kolejka, int nr_wierz );

int pKolejkaZdejmij ( pkolejka_t ** kolejka );

int pKolejkaAktualizuj (pkolejka_t ** kolejka, int nr_w);

int pKolejkaWypisz ( pkolejka_t * kolejka );

int dijkstra ( int w_start );

int dijTabFree( void );

#endif