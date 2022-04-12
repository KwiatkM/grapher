#include <stdio.h>
#include <stdlib.h>
#include "inout.h"
#include "bfs.h"

int bfsTabInit ( int x, int y ){
    tab_odw = malloc( x * y * sizeof(char));
    if (tab_odw == NULL) return 1;
    int i;
    for( i = 0; i < x*y; i++){
        tab_odw[i] = '0';
    }
    return 0;
}


// ----------------- KOLEJKA DO BFS -----------------
static int kolejkaDodaj (kolejka_t ** pierw_elem,  kolejka_t ** ost_elem, int nr_wierz ){
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

static int kolejkaZdejmij ( kolejka_t ** pierw_elem,  kolejka_t ** ost_elem ){
    if(*pierw_elem == NULL){
        *ost_elem = NULL;
        return -1;// gdy kolejka jest pusta 
    } 
    
    kolejka_t * tmpk = *pierw_elem;
    int tmp = (*pierw_elem)->nr_wierz;
    *pierw_elem = (*pierw_elem)->next;
    if(*pierw_elem == NULL) *ost_elem = NULL;
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


int bfs ( wierzcholek_t * graf,   int x, int y  ){
    // inicjalizacja kolejki
    kolejka_t * koniec = NULL;
    kolejka_t * poczatek= NULL;

    //inicjalizacja tablicy odwiedzonych
    bfsTabInit(x,y);

    int u = 0; // wierzchołek początkowy
    tab_odw[u] = '1';
    kolejkaDodaj(&poczatek, &koniec, u);
    while(poczatek != NULL){
        u = kolejkaZdejmij(&poczatek, &koniec);

        // wierzchołek po lewo
        if(u%y != 0){ // jeżeli u ma wierzchołek po lewo
            if((graf+u-1)->right > 0){ // jeżli istnieje przejście
                if(tab_odw[u-1] == '0'){ // jeżeli wierzchołek nie jest odwiedzony
                    kolejkaDodaj(&poczatek, &koniec, u-1);
                    tab_odw[u-1] = '1';
                }
            }
        }

        // wierzchołek na górze
        if((u-y)>=0){ 
            if((graf+u-y)->down > 0){ 
                if(tab_odw[u-y] == '0'){ 
                    kolejkaDodaj(&poczatek, &koniec, u-y);
                    tab_odw[u-y] = '1';
                }
            }
        }

        // wierzchołek po prawo
        if((u+1)%y != 0){ 
            if((graf+u)->right > 0){ 
                if(tab_odw[u+1] == '0'){ 
                    kolejkaDodaj(&poczatek, &koniec, u+1);
                    tab_odw[u+1] = '1';
                }
            }
        }

        // wierzchołek na dole
        if(u < (x*y)-y){ 
            if((graf+u)->down > 0){ 
                if(tab_odw[u+y] == '0'){ 
                    kolejkaDodaj(&poczatek, &koniec, u+y);
                    tab_odw[u+y] = '1';
                }
            }
        }  
    }
}

int wypiszTabBFS(int x, int y){
    int i;
    for(i = 0; i < x*y; i++){
        printf("wierzcholek %d: odw. %c\n", i, tab_odw[i]);
    }
    return 0;
}

int wypiszKolejke (kolejka_t * kolejka){
    printf("kolejka: ");
    while(kolejka != NULL){
        printf("%d -> ", kolejka->nr_wierz);
        kolejka = kolejka->next;
    }
    printf("\n");
    return 0;
}

int BFSTabFree(void){
    free(tab_odw);
    return 0;
}

int czySpojny( int x, int y ){
    // return 0 - niespójny
    // return 1 - spójny
    int i;
    for( i = 0; i < x*y; i++){
        if(tab_odw[i]=='0') return 0;
    }
    return 1;
}