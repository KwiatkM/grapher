#ifndef BFS
#define BFS

typedef struct e {
int nr_wierz;
struct e * next;
} kolejka_t;

extern char * tab_odw;

int bfsTabInit ( int x, int y );

int kolejkaDodaj (kolejka_t ** pierw_elem,  kolejka_t ** ost_elem, int nr_wierz );

int kolejkaZdejmij ( kolejka_t ** pierw_elem,  kolejka_t ** ost_elem );

int bfs (wierzcholek_t * graf,   int x, int y  );

int wypiszTabBFS(int x, int y);

int wypiszKolejke (kolejka_t * kolejka);


#endif