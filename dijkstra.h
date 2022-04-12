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

// inicjalizacja tablic poprzedników, odległości i odwiedzonych
int dijTabInit (int x, int y);

// dodawanie wierzhcołków do kolejki priorytetowej
static int pKolejkaDodaj ( pkolejka_t ** kolejka, int nr_wierz );

// zdejmowanie wierzchołków z kolejki priorytetowej
static int pKolejkaZdejmij ( pkolejka_t ** kolejka );

// przesunięcie wierzchołka w kolejce priorytetowej
static int pKolejkaAktualizuj (pkolejka_t ** kolejka, int nr_w);

// wypisanie kolejki (do testowania)
int pKolejkaWypisz ( pkolejka_t * kolejka );

// algorytm dijkstry
int dijkstra ( wierzcholek_t * graf,int x, int y, int w_start, int w_konc );

// wypisanie tablic (do testowania)
int wypiszTablice(int x, int y);

// zwolnienie pamięci na tablice
int dijTabFree( void );

// wypisuje ścieżke między dwoma wierzchołakmi na podane wyjście
int wypisz_sciezke( FILE * out, int wierzch_start, int wierzch_konc);

#endif