#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"

int bfsTabInit ( int x, int y ){

}

// ----------------- KOLEJKA DO BFS -----------------

int kolejkaDodaj ( kolejka_t ** ost_elem, int nr_wierz ){
    kolejka_t * tmp = malloc( sizeof(kolejka_t));
    tmp->next = NULL;
    tmp->nr_wierz = nr_wierz;

    if( *ost_elem == NULL){
        *ost_elem = tmp;
        return 0;
    }

    (*ost_elem)->next = tmp;
    (*ost_elem) = tmp;
    return 0;
    
}

int kolejkaZdejmij ( kolejka_t ** pierw_elem ){
    kolejka_t * tmpk = *pierw_elem;
    if(tmpk == NULL) return -1; // gdy kolejka jest pusta
    int tmp = (*pierw_elem)->nr_wierz;
    *pierw_elem = tmpk->next;
    free(tmpk);
    return tmp;

}

/*
aby kolejka działała poprawnie należy stworzyć dwa wskaźniki:
kolejka_t * koniec = NULL;
kolejka_t * poczatek= NULL;
jeden wskazuje na początek, a drugi na koniec kolejki

jeszcze żeby oba wskaźniki wskazywały na tą samą kolejkę należy po pierwszym 
dodaniu wartości do pustej kolejki należy przyrównać obydwa wskaźniki do siebie.

np.
kolejkaDodaj(&koniec, 9);
poczatek= koniec;
kolejkaDodaj(&koniec, 10);
a = kolejkaZdejmij(&poczatek)

gdy wszystki elementy z kolejki zostaną zdjęte, funkcja kolejkaZdejmij() będzie
wypisywać wartość -1 ()

*/
// ----------------------------------------------------------


int bfs ( void ){
    
}
