#ifndef BFS
#define BFS

typedef struct e {
int nr_wierz;
struct e * next;
} kolejka_t;

extern char * tab_odw;

// inicjalizacja tablicy odwiedzonych
int bfsTabInit ( int x, int y );

// resetuje wartości w tablicy do wartości takich jak przy inicjalizowaniu
int bfsTabReset ( int x, int y );

// dodeje element do kolejki
static int kolejkaDodaj (kolejka_t ** pierw_elem,  kolejka_t ** ost_elem, int nr_wierz );

// usuwa i zwraca element na początku kolejki
static int kolejkaZdejmij ( kolejka_t ** pierw_elem,  kolejka_t ** ost_elem );

// algorytm bfs
int bfs (wierzcholek_t * graf,   int x, int y, int w_start );

// (do testów) wypisuje tablice na std
int wypiszTabBFS(int x, int y);

// (do testów) wypisuje kolejke na std
int wypiszKolejke (kolejka_t * kolejka);

// zwalnia tablice odwiedzonych
int BFSTabFree(void);

// sprawdza spójność grafu na podstawie tablicy odwiedzonych
int czySpojny( int x, int y );

// (do testów) wyświetla wszystkie wierzchołki, które zostały odwiedzone
int wizualizuj_graf(FILE * out, int x, int y, int w_od, int w_do);

#endif