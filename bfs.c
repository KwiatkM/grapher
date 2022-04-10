#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"

int bfsTabInit ( int x, int y ){

}

// ----------------- KOLEJKA DO BFS -----------------

int kolejkaDodaj (kolejka_t ** pierw_elem,  kolejka_t ** ost_elem, int nr_wierz ){
    if(*ost_elem == NULL){
        kolejka_t * tmp = malloc( sizeof(kolejka_t));
        tmp->next = NULL;
        tmp->nr_wierz = nr_wierz;
        *ost_elem = tmp;
        *pierw_elem = tmp;
        return 0; 
    }
    kolejka_t * tmp = malloc( sizeof(kolejka_t));
    tmp->next = NULL;
    tmp->nr_wierz = nr_wierz;
    (*ost_elem)->next = tmp;
    *ost_elem = (*ost_elem)->next;
    return 0;

}


int kolejkaZdejmij ( kolejka_t ** pierw_elem,  kolejka_t ** ost_elem ){
    if(*pierw_elem == NULL){
        *ost_elem = NULL;
        return -1;// gdy kolejka jest pusta 
    } 
    
    kolejka_t * tmpk = *pierw_elem;
    int tmp = (*pierw_elem)->nr_wierz;
    *pierw_elem = (*pierw_elem)->next;
    free(tmpk);
    return tmp;

}

/*
aby kolejka działała poprawnie należy stworzyć dwa wskaźniki:
kolejka_t * koniec = NULL;
kolejka_t * poczatek= NULL;
jeden wskazuje na początek, a drugi na koniec kolejki

przykładowe wywołania funcji:

kolejkaDodaj (&poczatek, &koniec);
kolejkaZdejmij(&poczatek, &koniec);

gdy wszystki elementy z kolejki zostaną zdjęte, funkcja kolejkaZdejmij() będzie
wypisywać wartość -1 ()

*/
// ----------------------------------------------------------


int bfs ( void ){
    
}
