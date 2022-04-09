#ifndef BFS
#define BFS

typedef struct e {
int nr_wierz;
struct e * next;
} kolejka_t;

//char * tab_odw;

int bfsTabInit ( int x, int y );

int kolejkaDodaj ( kolejka_t ** ost_elem, int nr_wierz );

int kolejkaZdejmij ( kolejka_t ** pierw_elem );

int bfs ( void );


#endif