#ifndef DIJ
#define DIJ


#define INFINITY 99999999999.9

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

// (do testowania) wypisanie kolejki 
int pKolejkaWypisz ( pkolejka_t * kolejka );

// algorytm dijkstry
int dijkstra ( wierzcholek_t * graf,int x, int y, int w_start, int w_konc );

// (do testowania) wypisanie tablic 
int wypiszTablice(int x, int y);

// zwolnienie pamięci na tablice
int dijTabFree( void );

// wypisuje ścieżke między dwoma wierzchołakmi na podane wyjście
int wypisz_sciezke( FILE * out, int wierzch_start, int wierzch_konc);

// resetuje wartości w tablicach do wartości takich jak przy inicjalizowaniu
int dijTabReset (int x, int y);

// czysci kolejke
int pkolejkaFree (pkolejka_t * kolejka);

// usuwa wszystkie krawędzie na ścieżce do w_konc
int podzelGraf ( wierzcholek_t * graf, int x, int y, int w_konc);
#endif