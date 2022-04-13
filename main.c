#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "inout.h"
#include "bfs.h"
#include "dijkstra.h"

#define DEBUGG

int main(int argc, char **argv){
    int opt,  i, j, wymiar_x = 100, wymiar_y = 100, w_start = 0, w_konc = 1;
    double waga_od = 0.0, waga_do = 100.0, szansa = 1.0;
    char * tab_odw;
    FILE * file_out;
    FILE * path_out;
    char * file_out_graph = "file_out_graph.txt";
    char * file_out_path = "path_out.txt";
    while((opt = getopt(argc, argv, "o:i:p:x:y:f:t:c:s:k:")) != -1){      /*POCZATEK OBSLUGI OPCJI*/
        switch(opt){
            case 'o':{
                file_out_graph = optarg;
                break;
            }
            case 'i':{
                break;
            }
            case 'p':{
                file_out_path = optarg;
                break;
            }
            case 'x':{
                wymiar_x = atoi(optarg);
                break;
            }
            case 'y':{
                wymiar_y = atoi(optarg);
                break;
            }
            case 'f':{
                waga_od = atof(optarg);
                break;
            }
            case 't':{
                waga_do = atof(optarg);
                break;
            }
            case 'c':{
                szansa = atof(optarg);
                break;
            }
            case 's':{
                w_start = atof(optarg);
                break;
            }
            case 'k':{
                w_konc = atof(optarg);
                break;
            }
            case '?':{
                printf("Blad: Nie rozpoznano opcji!\n");
                return 1;
            }
            default:{
                break;
            }
        }
    }                                   /*KONIEC OBSLUGI OPCJI*/
    
    file_out = fopen(file_out_graph, "w");
    if(file_out == NULL){         
        printf("%s: Nie udalo sie wczytac pliku %s\n", argv[0], file_out_graph);
        return 1;
    }
    if(wymiar_x < 1) wymiar_x = 1;
    if(wymiar_x > 10000) wymiar_x = 10000;
    if(wymiar_y < 1) wymiar_y = 1;
    if(wymiar_y > 10000) wymiar_y = 10000;

    wierzcholek_t **graf = malloc(wymiar_x * sizeof(*graf));    /*alokujemy pamiec dla grafu*/
    if(graf == NULL){
        printf("Nie udalo sie zalokowac miejsca dla grafu\n");
        return 1;
    }
    for(i=0; i<wymiar_x; i++){
        graf[i] = malloc(wymiar_y * sizeof(*graf[i]));
        if(graf[i] == NULL){
            printf("Nie udalo sie zalokowac miejsca dla grafu\n");
            return 1;
        }
    }

    if(waga_od < 0.0) waga_od = 0.0;
    if(waga_od > 100.0) waga_od = 100.0; 
    if(waga_do > 100.0) waga_do = 100.0;
    if(waga_do < 0.0) waga_do = 0.0;
    if(waga_od > waga_do){      //jesli wagi beda w zlej relacji to zamieniamy ich wartosci ze soba
        double t = waga_do;
        waga_do = waga_od;
        waga_od = t;
    }
    if(szansa < 0.0) szansa = 0.0;
    if(szansa > 1.0) szansa = 1.0;
    createGraph(graf, wymiar_x, wymiar_y, waga_od, waga_do, szansa);  //wywolujemy funkcje tworzaca graf(nadajaca losowe przejcia i losowe wagi)
    
    saveGraph(graf, wymiar_x, wymiar_y, file_out);    //wywolujemy funkcje zapisujaca stworzony graf do pliku
    
   
    //** DIJKSTRY **
    if(w_start < 0)
        w_start = 0;
    if(w_konc < 0)
        w_konc = 0;
    if(w_start >= x*y)
        w_start = (x*y)-1;
    if(w_konc >= x*y)
        w_konc = (x*y)-1;

    dijkstra(graf, wymiar_x, wymiar_y, w_start, w_konc);

    path_out = fopen(file_out_path,"w");
    if(path_out == NULL){
        printf("%s: nie udalo sie zapisac wyniku w pliku %s\n", argv[0], file_out_graph);
        path_out = stdout;
    }
    
    //** BFS **
    if(bfs(graf, wymiar_x, wymiar_y) == 0)      //bfs - funkcja zwracajaca informacje o spojnosci grafu  
        printf("Graf nie jest spojny.\n");
    else
        printf("Graf jest spojny.\n");

    //** DIJKSTRY **
    dijkstra(graf, wymiar_x, wymiar_y, w_start, w_konc);

    path_out = fopen(file_out_path, "w");
    if(path_out == NULL){
        printf("%s: nie udalo sie zapisac wyniku w pliku %s\n", argv[0], file_out_path);
        path_out = stdout;
    }
    fprintf(path_out, "Wczytany graf:\n\n");
    fprintf(path_out, "Wymiary:\n");
    fprintf(path_out, "x = %d\n", wymiar_x);
    fprintf(path_out, "y = %d\n\n", wymiar_y);
    fprintf(path_out, "Wagi:\n");
    fprintf(path_out, "minimalna: %f\n", waga_od);
    fprintf(path_out, "maksymalna: %f\n\n", waga_do);
    fprintf(path_out, "Szansa na krawedz:\n");
    fprintf(path_out, "szansa = %0.2f%%\n\n", szansa*100);
    fprintf(path_out, "Indeks wierzcholka startowego: %d\n", w_start);
    fprintf(path_out, "Indeks wierzcholka koncowego: %d\n\n", w_konc);
    fprintf(path_out, "Znaleziona najkrotsza sciezka:\n");
    wypisz_sciezke(path_out, w_start, w_konc);
    fprintf(path_out,"\n");
    fprintf(path_out, "Dlugosc sciezki:\n");
    fprintf(path_out, "%lf\n\n", odleglosc[w_konc]);;
    if(bfs(graf, wymiar_x, wymiar_y) == 0)          //bfs - zwraca informacje o spojnosci grafu  
        fprintf(path_out, "Graf nie jest spojny.\n");
    else
        fprintf(path_out, "Graf jest spojny.\n");
   
    fclose(file_out);
    fclose(path_out);

    free(tab_odw);          //zwalniamy dla tab odwiedzonych z bfsa
    free(poprzednik);
    free(odleglosc);        //zwalniamy dla dijkstry
    free(odwiedzono);

    for(i=0; i<wymiar_x; i++)          //zwalniamy dla grafu
        free(graf[i]);  
    free(graf);

    return 0;
}