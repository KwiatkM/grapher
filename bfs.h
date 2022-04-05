#ifndef BFS
#define BFS

typedef struct e {
int nr_wierz;
struct e * next;
} kolejka_t;

char * tab_odw;

int bfsTabInit ( int x, int y );

kolejka_t * kolejkaInit ( void );

int kolejkaDodaj ( int nr_wierz );

int kolejkaZdejmij ( void );

int bfs ( void );


#endif