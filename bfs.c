#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inout.h"       //for wierzcholek_t structure for bfs function
#include "bfs.h"

void bfsTabInit (int wymiar_x, int wymiar_y){
    char **tab_odw = malloc(wymiar_x * sizeof(*tab_odw));       //alokujemy pamiec dla tablicy odwiedzonych wierzcholkow
    for(x=0; x<wymiar_x; x++)
        tab_odw[x] = malloc(wymiar_y * sizeof(*tab_odw[x]));
    
    for(x=0; x<wymiar_x; x++)
        for(y=0; y<wymiar_y; y++)     
            strcpy(&tab_odw[x][y], "0");       //<--- domyslnie kazdy wierzcholek jest nieodwiedzony
}

void kolejkaInit (void){
    kolejka_t * poczatek = NULL;
    kolejka_t * koniec = NULL;
    kolejkaDodaj(&poczatek, &koniec, 0);    //<--- na poczatku dodajemy pierwszy wierzcholek do kolejki(z numerem 0)
    strcpy(&tab_odw[0][0], "1");    //<--- dodajemy wierzchołek z nr_wierz == 0 do odwiedzonych
}

int kolejkaDodaj (kolejka_t ** first_elem, kolejka_t ** last_elem, int nr_wierz){
    if(*last_elem == NULL){
        kolejka_t * tmp = malloc(1 * sizeof(*tmp));
        tmp->next = NULL;
        tmp->nr_wierz = nr_wierz;
        *last_elem = tmp;
        *first_elem = tmp;
        return 0; 
    }
    kolejka_t * tmp = malloc(1 * sizeof(*tmp));
    tmp->next = NULL;
    tmp->nr_wierz = nr_wierz;
    (*last_elem)->next = tmp;
    (*last_elem) = (*last_elem)->next;
    return 0;
}

int kolejkaZdejmij (kolejka_t ** first_elem, kolejka_t ** last_elem){
    if(*first_elem == NULL){
        *last_elem = NULL;        
        return -1;              //<-- jesli kolejka jest pusta(nie mamy juz co zdejmowac z kolejki i zwracamy -1)
    }

    kolejka_t * tmpk = *first_elem;

    int nr = (*first_elem)->nr_wierz;       //<-- pobieramy numer wierzcholka z poczatku kolejki
    
    *first_elem = (*first_elem)->next;    //<-- przesuwamy poczatek o nastepny element     

    free(tmpk);       //<-- usuwamy poprzedni element
    return nr;       //<-- zwracamy pobrany numer wierzcholka
}

int bfs (wierzcholek_t **graf, int wymiar_x, int wymiar_y, char **tab_odw){
    int nr_wierz_pull, x_wierz_pull, y_wierz_pull, nr_wierz_add;
    nr_wierz_pull = kolejkaZdejmij(&poczatek, &koniec);   //<--- pobieramy nr_wierz z początku kolejki i zapisujemy go do nr_wierz_pull
    do { 
        y_wierz_pull = nr_wierz_pull % wymiar_y;                            //wyliczamy współrzędne pobranego wierzcholka                                  
        x_wierz_pull = (nr_wierz_pull - y_wierz_pull) / wymiar_y;            //i zapisujemy je do zmiennych: x_wierz_pull i y_wierz_pull
                                                        //gdy juz mamy wspolrzedne pobranego wierzcholka to sprawdzamy jego sasiadow
        if(x_wierz_pull == 0 && y_wierz_pull == 0){                 //NIE SPRAWDZAMY NA GORZE I LEWO
            if(strcmp(&tab_odw[x_wierz_pull][y_wierz_pull + 1], "0") == 0){         //<-- PRAWO jesli sasiad po prawo jest nieodwiedzony
                if(graf[x_wierz_pull][y_wierz_pull].right != -1.1){                 //<-- i jesli do sasiada po prawo jest przejscie
                    nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull + 1);    //<-- to wyliczamy nr tego wierzcholka
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             //<-- i dodajemy go na koniec kolejki
                    strcpy(&tab_odw[x_wierz_pull][y_wierz_pull + 1], "1");               //<-- i dodajemy go do odwiedzonych
                }
            }
            if(strcmp(&tab_odw[x_wierz_pull + 1][y_wierz_pull], "0") == 0){         //<-- DOL
                if(graf[x_wierz_pull][y_wierz_pull].down != -1.1){                 
                    nr_wierz_add = (x_wierz_pull + 1) * wymiar_y + y_wierz_pull;    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull + 1][y_wierz_pull], "1");               
                }
            }
        }
        if(x_wierz_pull == 0 && y_wierz_pull != 0){                     //NIE SPRAWDZAMY NA GORZE
            if(strcmp(&tab_odw[x_wierz_pull][y_wierz_pull - 1], "0") == 0){         //<-- LEWO
                if(graf[x_wierz_pull][y_wierz_pull - 1].right != -1.1){                 
                    nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull - 1);    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull][y_wierz_pull - 1], "1");               
                }
            }
            if(strcmp(&tab_odw[x_wierz_pull][y_wierz_pull + 1], "0") == 0){         //<-- PRAWO
                if(graf[x_wierz_pull][y_wierz_pull].right != -1.1){                 
                    nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull + 1);    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull][y_wierz_pull + 1], "1");              
                }
            }
            if(strcmp(&tab_odw[x_wierz_pull + 1][y_wierz_pull], "0") == 0){         //<-- DOL
                if(graf[x_wierz_pull][y_wierz_pull].down != -1.1){                 
                    nr_wierz_add = (x_wierz_pull + 1) * wymiar_y + y_wierz_pull;    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull + 1][y_wierz_pull], "1");               
                }
            }
        }
        if(x_wierz_pull != 0 && y_wierz_pull == 0){                 //NIE SPRAWDZAMY NA LEWO
            if(strcmp(&tab_odw[x_wierz_pull - 1][y_wierz_pull], "0") == 0){         //<-- GORA
                if(graf[x_wierz_pull - 1][y_wierz_pull].down != -1.1){                 
                    nr_wierz_add = (x_wierz_pull - 1) * wymiar_y + y_wierz_pull;    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull - 1][y_wierz_pull], "1");               
                }
            }
            if(strcmp(&tab_odw[x_wierz_pull][y_wierz_pull - 1], "0") == 0){         //<-- LEWO
                if(graf[x_wierz_pull][y_wierz_pull - 1].right != -1.1){                 
                    nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull - 1);    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull][y_wierz_pull - 1], "1");               
                }
            }
            if(strcmp(&tab_odw[x_wierz_pull + 1][y_wierz_pull], "0") == 0){         //<-- DOL
                if(graf[x_wierz_pull][y_wierz_pull].down != -1.1){                 
                    nr_wierz_add = (x_wierz_pull + 1) * wymiar_y + y_wierz_pull;    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull + 1][y_wierz_pull], "1");               
                }
            }
        }
        else{                                               //SPRAWDZAMY W KAZDYM KIERUNKU
            if(strcmp(&tab_odw[x_wierz_pull - 1][y_wierz_pull], "0") == 0){         //<-- GORA
                if(graf[x_wierz_pull - 1][y_wierz_pull].down != -1.1){                 
                    nr_wierz_add = (x_wierz_pull - 1) * wymiar_y + y_wierz_pull;    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull - 1][y_wierz_pull], "1");               
                }
            }
            if(strcmp(&tab_odw[x_wierz_pull][y_wierz_pull - 1], "0") == 0){         //<-- LEWO
                if(graf[x_wierz_pull][y_wierz_pull - 1].right != -1.1){                 
                    nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull - 1);    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull][y_wierz_pull - 1], "1");               
                }
            }
            if(strcmp(&tab_odw[x_wierz_pull][y_wierz_pull + 1], "0") == 0){         //<-- PRAWO
                if(graf[x_wierz_pull][y_wierz_pull].right != -1.1){                 
                    nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull + 1);    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull][y_wierz_pull + 1], "1");              
                }
            }
            if(strcmp(&tab_odw[x_wierz_pull + 1][y_wierz_pull], "0") == 0){         //<-- DOL
                if(graf[x_wierz_pull][y_wierz_pull].down != -1.1){                 
                    nr_wierz_add = (x_wierz_pull + 1) * wymiar_y + y_wierz_pull;    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    strcpy(&tab_odw[x_wierz_pull + 1][y_wierz_pull], "1");               
                }
            }
        }
        nr_wierz_pull = kolejkaZdejmij(&poczatek, &koniec);       //zdejmujemy kolejny nr_wierz z kolejki
    } while(nr_wierz_pull != -1);
    //*GDY KOLEJKA JEST PUSTA*
    for(x=0; x<wymiar_x; x++)              //sprawdzamy tab_odw
        for(y=0; y<wymiar_y; y++)
            if(strcmp(&tab_odw[x][y], "0") == 0)   //jeśli znajdziemy co najmniej jeden wierzcholek nieodwiedzony, to graf nie jest spojny
                return 0;
    return 1;           //jesli kazdy wierzcholek jest odwiedzony to graf jest spojny
}
