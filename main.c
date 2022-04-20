#include "inout.h"
#include "dijkstra.h"
#include "bfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define DEBUGG

// tablice do dijkstry
int * poprzednik;
double * odleglosc;
char * odwiedzono;

// tablica do BFS
char * tab_odw;

int main(int argc, char** argv){

    wierzcholek_t * graf;
    char * file_out_graph = "file_out_graph";
    FILE * out;
    FILE * path_out;
    FILE * in;
    char * file_in = NULL;
    char * file_out_path = "path_out";
    int x = 10, y = 10, wierzcholek_1 = 0, wierzcholek_2 = 1;
    double waga_od = 0.0, waga_do = 100.0, szansa = 1.0;
    int czy_podzial = 0; // 0 = nie, cokolwiek innego = tak

    int i = 1;
    // obsługa argumentów wywołania
    for(i = 1; i < argc; i += 2){
        if(argv[i][0] != '-'){
            printf("niepoprawny argument wywolania: %s\n", argv[i]);
            return 1;
        }
        switch(argv[i][1])
        {
            case 'o':
            if(i+1 < argc)
                file_out_graph = argv[i+1];  
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            }                
            break;

            case 'i':
            if(i+1 < argc)
                file_in = argv[i+1];  
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            }      
            break;
            
            case 'p':
            if(i+1 < argc)
                file_out_path = argv[i+1];
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            }        
            break;

            case 'x':
            if(i+1 < argc)
                x = atoi(argv[i+1]);
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            } 
            break;

            case 'y':
            if(i+1 < argc)
                y = atoi(argv[i+1]);
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            } 
            break;

            case 'f':
            if(i+1 < argc)
                waga_od = atof(argv[i+1]);
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            } 
            break;

            case 't':
            if(i+1 < argc)
                waga_do = atof(argv[i+1]);
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            } 
            break;

            case 'c':
            if(i+1 < argc)
                szansa = atof(argv[i+1]);
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            } 
            break;

            case 's':
            if(i+1 < argc)
                wierzcholek_1 = atoi(argv[i+1]);
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            } 
            break;

            case 'k':
            if(i+1 < argc)
                wierzcholek_2 = atoi(argv[i+1]);
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            } 
            break;

            case 'd':
            if(i+1 < argc)
                czy_podzial = atoi(argv[i+1]);
            if(argv[i+1][0] == '-'){
                printf("niepoprawna wartosc argument wywolania: %s\n", argv[i+1]);
                return 1;
            } 
            break;

            

            default:
            printf("bledne argumenty wejsciowe!\n");
            return 1;

    
        }

    }


#ifdef DEBUG
printf("plik wyjsciowy grafu: %s\n", file_out_graph);
printf("plik wejsciowy grafu: %s\n", file_in);
printf("plik wyjsciowy z rozwiazaniem: %s\n", file_out_path);
printf("rozmiar x grafu: %d\n", x);
printf("rozmiar y grafu: %d\n", y);
printf("wierzcholek startowy sciezki: %d\n", wierzcholek_1);
printf("wierzcholek koncowy sciezki: %d\n", wierzcholek_2);
printf("waga od: %f\n", waga_od);
printf("waga do: %f\n", waga_do);
printf("szansa: %f\n\n", szansa);
#endif

// jeśli podano plik wejściowy z grafem

dijTabInit(x,y); // inicjalizacja tablic do dijkstry ( musi być tutaj aby poprawnie podzelić graf)

if (file_in != NULL)
{

    in = fopen(file_in, "r");
    if (in == NULL)
    {
        fprintf(stderr, "%s: Nie udalo sie otworzyc pliku %s\n", argv[0], file_in);
        return 1;
    }
    fscanf(in, "%d %d\n", &x, &y);

    graf = kontenerInit(x, y);
    if (graf == NULL)
    {
        fprintf(stderr,"%s: nie udalo sie utworzyc struktury przechowujacej graf\n", argv[0]);
        return 1;
    }

    if (wczytaj_graf(graf, x, y, in) == 1)
    {
        fclose(in);
        fprintf(stderr, "%s: plik %s zawiera niepoprawnie zapisany graf\n", argv[0], file_in);
        return 1;
    }
    fclose(in);
}
else // jeśli nie podano pliku wejściowego
{

    graf = kontenerInit(x, y);
    if (graf == NULL)
    {
        fprintf(stderr,"%s: nie udalo sie utworzyc struktury przechowujacej graf\n", argv[0]);
        return 1;
    }

    if(waga_od < 0.0) waga_od = 0.0;
    if(waga_od > 100.0) waga_od = 100.0;
    if(waga_do > 100.0) waga_do = 100.0;
    if(waga_do < 0.0) waga_do = 0.0;
    if(waga_od > waga_do){
        int tmp = waga_do;
        waga_do = waga_od;
        waga_od = tmp;

    if(szansa < 0.0) szansa = 0.0;
    if(szansa > 1.0) szansa = 1.0;
    
    }
    gen_graf(graf, x, y, waga_od, waga_do, szansa);

    // --------- dzielenie grafu -------------
    if(czy_podzial != 0){
    srand(time(NULL));
    int w_konc = (x*y)-1 - rand() % y;
    int w_start = rand() % y;
    dijkstra(graf, x,y,w_start, w_konc);
    podzelGraf(graf,x,y,w_konc);
    dijTabReset(x,y);
    }
    // ---------------------------------------

    out = fopen(file_out_graph, "w");
    if (out == NULL)
    {
        fprintf(stderr,"%s: nie udalo sie otworzyc pliku %s\n", argv[0], file_out_graph);
    }
    zapiszGraf(graf, x, y, out);
    fclose(out);
}

if(wierzcholek_1 < 0) wierzcholek_1 = 0;
if(wierzcholek_2 < 0) wierzcholek_2 = 0;
if(wierzcholek_2 >= x*y) wierzcholek_2 = (x*y)-1;
if(wierzcholek_1 >= x*y) wierzcholek_1 = (x*y)-1;


dijkstra(graf, x, y, wierzcholek_1, wierzcholek_2);

#ifdef DEBUG
wypiszTablice(x,y);
#endif

bfsTabInit(x,y); 
bfs(graf, x, y, wierzcholek_1);

#ifdef DEBUG
wypiszTabBFS(x,y);
#endif

path_out = fopen(file_out_path,"w");
if(path_out == NULL){
    fprintf(stderr,"%s: nie udalo sie zapisac wyniku w pliku %s\n", argv[0], file_out_graph);
    path_out = stdout;
}

fprintf(path_out, "Wczytany graf:\n\n");
fprintf(path_out, "Wymiary:\n");
fprintf(path_out, "x = %d\n", x);
fprintf(path_out, "y = %d\n\n", y);
fprintf(path_out, "Wagi:\n");
fprintf(path_out, "minimalna: %f\n", waga_od);
fprintf(path_out, "maksymalna: %f\n\n", waga_do);
fprintf(path_out, "Szansa na krawedz:\n");
fprintf(path_out, "szansa = %0.2f%%\n\n", szansa*100);
fprintf(path_out, "czy podzielono:\n");
fprintf(path_out, "%s\n\n", czy_podzial == 0 ? "nie" : "tak");
fprintf(path_out, "Indeks wierzcholka startowego: %d\n", wierzcholek_1);
fprintf(path_out, "Indeks wierzcholka koncowego: %d\n\n", wierzcholek_2);
fprintf(path_out, "Znaleziona najkrotsza sciezka:\n");
wypisz_sciezke(path_out, wierzcholek_1,wierzcholek_2);
fprintf(path_out,"\n");
fprintf(path_out, "Dlugosc sciezki:\n");
fprintf(path_out, "%lf\n\n", odleglosc[wierzcholek_2] == INFINITY ? 0 : odleglosc[wierzcholek_2]);
fprintf(path_out, "Graf spojny:\n");
fprintf(path_out, "%s\n", czySpojny(x,y) == 1 ? "tak" : "nie");

fclose(path_out);

#ifdef DEBUG
FILE * do_testu = fopen("widok_grafu", "w");
wizualizuj_graf(do_testu,x,y, wierzcholek_1, wierzcholek_2);
fclose(do_testu);
#endif

BFSTabFree();
dijTabFree();
free(graf);
printf("koniec");
return 0;
}


