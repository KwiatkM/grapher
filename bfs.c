#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inout.h"       //for wierzcholek_t structure for bfs function
#include "bfs.h"

char *tab_odw;

static int bfsTabInit (int wymiar_x, int wymiar_y){
    tab_odw = malloc(wymiar_x * wymiar_y * sizeof(*tab_odw));       //<-- alokujemy pamiec dla tablicy odwiedzonych wierzcholkow
    for(x=0; x < wymiar_x * wymiar_y; x++)    
        tab_odw[x] = '0';
    if(tab_odw == NULL){
        printf("Nie udalo sie zalokowac miejsca dla tab_odw\n");
        return 1;
    }
    return 0;
}

static void kolejkaInit (kolejka_t **first_elem, kolejka_t **last_elem){
    kolejkaDodaj(first_elem, last_elem, 0);    //<--- na poczatku dodajemy pierwszy wierzcholek do kolejki(z numerem 0)
    tab_odw[0] = '1';
}

static int kolejkaDodaj (kolejka_t **first_elem, kolejka_t **last_elem, int nr_wierz){
    if(*last_elem == NULL){
        kolejka_t *tmp = malloc(1 * sizeof(*tmp));
        tmp->next = NULL;
        tmp->nr_wierz = nr_wierz;
        *last_elem = tmp;
        *first_elem = tmp;
        //printf("Dodano: %d\n", nr_wierz);
        return 0; 
    }
    kolejka_t *tmp = malloc(1 * sizeof(*tmp));
    tmp->next = NULL;
    tmp->nr_wierz = nr_wierz;
    (*last_elem)->next = tmp;
    (*last_elem) = (*last_elem)->next;
    //printf("Dodano: %d\n", nr_wierz);
    return 0;
}

static int kolejkaZdejmij (kolejka_t **first_elem, kolejka_t **last_elem){
    if(*first_elem == NULL){
        *last_elem = NULL;        
        return -1;              //<-- jesli kolejka jest pusta(nie mamy juz co zdejmowac z kolejki i zwracamy -1)
    }
    kolejka_t *tmpk = *first_elem;
    
    nr = (*first_elem)->nr_wierz;       //<-- pobieramy numer wierzcholka z poczatku kolejki
    *first_elem = (*first_elem)->next;    //<-- przesuwamy poczatek o nastepny element     
    if(*first_elem == NULL)
        *last_elem = NULL;
    free(tmpk);       //<-- usuwamy poprzedni element
    return nr;       //<-- zwracamy pobrany numer wierzcholka
}

int bfs (wierzcholek_t **graf, int wymiar_x, int wymiar_y){
    kolejka_t *poczatek = NULL;
    kolejka_t *koniec = NULL;
    bfsTabInit(wymiar_x, wymiar_y);
    kolejkaInit(&poczatek, &koniec);
    int nr_wierz_pull, x_wierz_pull, y_wierz_pull, nr_wierz_add;
    nr_wierz_pull = kolejkaZdejmij(&poczatek, &koniec);   //<--- pobieramy nr_wierz z początku kolejki i zapisujemy go do nr_wierz_pull
    //printf("Zdjeto: %d\n", nr_wierz_pull);
    while(nr_wierz_pull != -1){ 
        y_wierz_pull = nr_wierz_pull % wymiar_y;                            //wyliczamy współrzędne pobranego wierzcholka                                  
        x_wierz_pull = (nr_wierz_pull - y_wierz_pull) / wymiar_y;            //i zapisujemy je do zmiennych: x_wierz_pull i y_wierz_pull
                                                //gdy juz mamy wspolrzedne pobranego wierzcholka to sprawdzamy jego sasiadow
        if(x_wierz_pull == 0 && y_wierz_pull == 0){                 //NIE SPRAWDZAMY NA GORZE I LEWO
            nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull + 1); //<-- wyliczamy nr prawego wierzcholka
            if(tab_odw[nr_wierz_add] == '0'){         //<-- PRAWO jesli sasiad po prawo jest nieodwiedzony
                if(graf[x_wierz_pull][y_wierz_pull].right != -1.1){                 //<-- i jesli do sasiada po prawo jest przejscie   
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             //<-- i dodajemy go na koniec kolejki
                    tab_odw[nr_wierz_add] = '1';               //<-- i dodajemy go do odwiedzonych
                }
            }
            nr_wierz_add = (x_wierz_pull + 1) * wymiar_y + y_wierz_pull; 
            if(tab_odw[nr_wierz_add] == '0'){         //<-- DOL
                if(graf[x_wierz_pull][y_wierz_pull].down != -1.1){                 
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';               
                }
            }
        }
        if(x_wierz_pull == 0 && y_wierz_pull != 0){                     //NIE SPRAWDZAMY NA GORZE
            nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull - 1);
            if(tab_odw[nr_wierz_add] == '0'){         //<-- LEWO
                if(graf[x_wierz_pull][y_wierz_pull - 1].right != -1.1){                 
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';               
                }
            }
            nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull + 1);
            if(tab_odw[nr_wierz_add] == '0'){         //<-- PRAWO
                if(graf[x_wierz_pull][y_wierz_pull].right != -1.1){                     
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';              
                }
            }
            nr_wierz_add = (x_wierz_pull + 1) * wymiar_y + y_wierz_pull;
            if(tab_odw[nr_wierz_add] == '0'){         //<-- DOL
                if(graf[x_wierz_pull][y_wierz_pull].down != -1.1){                 
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';               
                }
            }
        }
        if(x_wierz_pull != 0 && y_wierz_pull == 0){                 //NIE SPRAWDZAMY NA LEWO
            nr_wierz_add = (x_wierz_pull - 1) * wymiar_y + y_wierz_pull;
            if(tab_odw[nr_wierz_add] == '0'){         //<-- GORA
                if(graf[x_wierz_pull - 1][y_wierz_pull].down != -1.1){                 
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';               
                }
            }
            nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull - 1);
            if(tab_odw[nr_wierz_add] == '0'){         //<-- LEWO
                if(graf[x_wierz_pull][y_wierz_pull - 1].right != -1.1){                     
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';               
                }
            }
            nr_wierz_add = (x_wierz_pull + 1) * wymiar_y + y_wierz_pull;
            if(tab_odw[nr_wierz_add] == '0'){         //<-- DOL
                if(graf[x_wierz_pull][y_wierz_pull].down != -1.1){                 
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';               
                }
            }
        }
        else{                                               //SPRAWDZAMY W KAZDYM KIERUNKU
            nr_wierz_add = (x_wierz_pull - 1) * wymiar_y + y_wierz_pull;
            if(tab_odw[nr_wierz_add] == '0'){         //<-- GORA
                if(graf[x_wierz_pull - 1][y_wierz_pull].down != -1.1){                    
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';               
                }
            }
            nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull - 1);
            if(tab_odw[nr_wierz_add] == '0'){         //<-- LEWO
                if(graf[x_wierz_pull][y_wierz_pull - 1].right != -1.1){                 
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';               
                }
            }
            nr_wierz_add = x_wierz_pull * wymiar_y + (y_wierz_pull + 1);
            if(tab_odw[nr_wierz_add] == '0'){         //<-- PRAWO
                if(graf[x_wierz_pull][y_wierz_pull].right != -1.1){                 
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';              
                }
            }
            nr_wierz_add = (x_wierz_pull + 1) * wymiar_y + y_wierz_pull;
            if(tab_odw[nr_wierz_add] == '0'){         //<-- DOL
                if(graf[x_wierz_pull][y_wierz_pull].down != -1.1){                 
                    kolejkaDodaj(&poczatek, &koniec, nr_wierz_add);                             
                    tab_odw[nr_wierz_add] = '1';               
                }
            }
        }
        nr_wierz_pull = kolejkaZdejmij(&poczatek, &koniec);       //zdejmujemy kolejny nr_wierz z kolejki
        //printf("Zdjeto: %d\n", nr_wierz_pull);
    }
    //*GDY KOLEJKA JEST PUSTA*
    for(x=0; x < wymiar_x * wymiar_y; x++)              //sprawdzamy tab_odw
        if(strcmp(&tab_odw[x], "0") == 0)   //jeśli znajdziemy co najmniej jeden wierzcholek nieodwiedzony, to graf nie jest spojny
            return 0;
    return 1;           //jesli kazdy wierzcholek jest odwiedzony to graf jest spojny
}
