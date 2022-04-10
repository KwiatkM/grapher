#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "inout.h"
#include "bfs.h"

int main(int argc, char **argv){
    int opt, wymiar_x, wymiar_y, i, j;
    double waga_od, waga_do, szansa;
    FILE * file_out_graph;
    while((opt = getopt(argc, argv, "o:i:p:x:y:f:t:c:s:k:")) != -1){      /*POCZATEK OBSLUGI OPCJI*/
        switch(opt){
            case 'o':{
                file_out_graph = fopen(optarg, "w");
                if(file_out_graph == NULL){             //jesli nie uda sie wczytac file_out_graph:
                    fprintf(stderr, "Blad: Nie udalo sie wczytac pliku!\n");
                    return EXIT_FAILURE;
                }
                break;
            }
            case 'i':{
                break;
            }
            case 'p':{
                break;
            }
            case 'x':{
                if(optarg == NULL)  //jesli nie podamy -x to wymiar_x = 100
                    wymiar_x = 100;
                else                //jesli podamy, to:
                    wymiar_x = atoi(optarg) >= 1 && atoi(optarg) <= 10000? atoi(optarg) : 100;  //jesli podamy wartosc w zakresie to dobrze, jesli nie to wymiar_x = 100
                break;
            }
            case 'y':{
                if(optarg == NULL)   //jesli nie podamy -y to wymiar_y = 100
                    wymiar_y = 100;
                else                   //jeśli podamy, to:
                    wymiar_y = atoi(optarg) >= 1 && atoi(optarg) <= 10000? atoi(optarg) : 100;  //jesli podamy wartosc w zakresie to dobrze, jesli nie to wymiar_y = 100
                break;
            }
            case 'f':{
                if(optarg == NULL) //jesli nie podamy -f to waga_od = 0.0
                    waga_od = 0.0;
                else
                    waga_od = atof(optarg) >= 0.0 && atof(optarg) <= 100.0? atof(optarg) : 0.0;  //jesli podamy wartosc w zakresie to dobrze, jesli nie to waga_od = 0.0
                break;
            }
            case 't':{
                if(optarg == NULL) //jesli nei podamy -t to waga_do = 100.0
                    waga_do = 100.0;
                else
                    waga_do = atof(optarg) >= 0.0 && atof(optarg) <= 100.0? atof(optarg) : 100.0;  //jesli podamy wartosc w zakresie to dobrze, jesli nie to waga_do = 100.0
                break;
            }
            case 'c':{
                if(optarg == NULL) //jesli nie podamy -c, to szansa = 1.0
                    szansa = 1.0;
                else
                    szansa = atof(optarg) >= 0.0 && atof(optarg) <= 1.0? atof(optarg) : 1.0;   //jesli podamy wartosc w zakresie to dobrze, jesli nie to szansa = 1.0
                break;
            }
            case 's':{
                break;
            }
            case 'k':{
                break;
            }
            case '?':{
                fprintf(stderr, "Blad: Nie rozpoznano opcji!\n");
                return EXIT_FAILURE;
            }
            default:{
                if(waga_od > waga_do){     //jesli wagi beda w zlej relacji to zamieniamy ich wartosci ze soba
                    double t = waga_do;
                    waga_do = waga_od;
                    waga_od = t;
                }
                break;
            }
        }
    }                                   /*KONIEC OBSLUGI OPCJI*/
    
    wierzcholek_t **graf = malloc(wymiar_x * sizeof(*graf));    /*alokujemy pamiec dla grafu*/
    for(i=0; i<wymiar_x; i++)
        graf[i] = malloc(wymiar_y * sizeof(*graf[i]));
    
    

    createGraph(graf, wymiar_x, wymiar_y, waga_od, waga_do, szansa);  //wywolujemy funkcje tworzaca graf(nadajaca losowe przejcia i losowe wagi)
    
    saveGraph(graf, wymiar_x, wymiar_y, file_out_graph);    //wywolujemy funkcje zapisujaca stworzony graf do pliku
    /*
    //POCZATEK BFS
    bfsTabInit(wymiar_x, wymiar_y);         //wywolujemy funkcje inicjująca tab_odw dla BFS-a(alokującą pamięć i nadająca podstawowe parametry)
    kolejkaInit();                      //inicjujemy kolejke dla BFS(alokujemy pamiec dla pierwszej struktury, dodajemy do kolejki nr_wierz = 0 i dodajemy go do odwiedzonych)
    if(bfs(graf, wymiar_x, wymiar_y) == 0)      //funkcja zwracajaca informacje o spojnosci grafu  
        printf("Graf nie jest spojny.\n");
    else
        printf("Graf jest spojny.\n");
    //KONIEC BFS
    */
   
    char **tab_odw = malloc(wymiar_x * sizeof(*tab_odw));       //alokujemy pamiec dla tablicy odwiedzonych wierzcholkow
    for(x=0; x<wymiar_x; x++)
        tab_odw[x] = malloc(wymiar_y * sizeof(*tab_odw[x]));
    
    for(x=0; x<wymiar_x; x++)
        for(y=0; y<wymiar_y; y++)     
            strcpy(&tab_odw[x][y], "0");       //<--- domyslnie kazdy wierzcholek jest nieodwiedzony
    
    kolejka_t * poczatek = NULL;
    kolejka_t * koniec = NULL;
    kolejkaDodaj(&poczatek, &koniec, 0);    //<--- na poczatku dodajemy pierwszy wierzcholek do kolejki(z numerem 0)
    strcpy(&tab_odw[0][0], "1");    //<--- dodajemy wierzchołek z nr_wierz == 0 do odwiedzonych

    if(bfs(graf, wymiar_x, wymiar_y, tab_odw) == 0)      //funkcja zwracajaca informacje o spojnosci grafu  
        printf("Graf nie jest spojny.\n");
    else
        printf("Graf jest spojny.\n");

    
    for(i=0; i<wymiar_x; i++)       //zwalniamy pamiec dla tab_odw
        free(tab_odw[i]);
    free(tab_odw);
    
    for(i=0; i<wymiar_x; i++)          //zwalniamy pamiec dla grafu
        free(graf[i]);  
    free(graf);

    fclose(file_out_graph);
    return 0;
}