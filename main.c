#include "inout.h"
#include "dijkstra.h"
#include "bfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUGG

int * poprzednik;
double * odleglosc;
char * odwiedzono;

int main(int argc, char** argv){

    wierzcholek_t * graf;
    char * file_out_graph = "file_out_graph";
    FILE * out;
    FILE * in;
    char * file_in = NULL;
    char * file_out_path = "stdout";
    int x = 5, y = 5, wierzcholek_1 = 0, wierzcholek_2 = 1;
    double waga_od = 0.0, waga_do = 100.0, szansa = 1.0;

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


if(file_in != NULL){
    

in = fopen(file_in, "r");
if ( in == NULL){
    fprintf(stderr, "%s: Nie udalo sie otworzyc pliku %s\n", argv[0], file_in);
    return 1;
}
fscanf(in, "%d %d\n", &x, &y);
graf = kontenerInit(x,y);

if(wczytaj_graf(graf, x, y, in) == 1){
    fclose(in);
    fprintf(stderr, "%s: plik %s zawiera niepoprawnie zapisany graf\n", argv[0], file_in);
    return 1;
};
fclose(in);
} 
else
{
graf = kontenerInit(x,y);

// wypełnienie grafu losowymi wartościami krawędzi
srand(time(NULL));
for (i = 0; i< x*y; i++){

    // sprawdzenie, czy wierzchołek ma krawędź z prawej
    if((i+1)%y != 0){
        if((double)rand()/RAND_MAX < szansa)    
            (graf+i)->right = ((double)rand()/RAND_MAX) * (waga_od + (waga_do - waga_od));
    }

    // sprawdzenie, czy wierzchołek ma krawędź u dołu
    if(i < ((x*y)-y)){
        if((double)rand()/RAND_MAX < szansa) 
            (graf+i)->down = ((double)rand()/RAND_MAX) * (waga_od + (waga_do - waga_od));
    }
}

out = fopen( file_out_graph, "w" );
if(out == NULL){
    printf("%s: nie udalo sie otworzyc pliku %s\n", argv[0], file_out_graph);
}
zapiszGraf(graf,x,y,out);
fclose(out);
}

pkolejka_t * kolejka = NULL;


/*  
// sprawdzienie, czy udało się przydzielić pamięć na tablice

if(dijTabInit(x,y)==1){
    printf("%s: nie udalo sie utworzyc tablic potrzebnych do algorytmu Dijkstry\n", argv[0]);
    return 1; // trzeba też tak zrobić z alokacją pamięci na strukture grafu
}
*/

free(graf);
printf("koniecc");
return 0;
}


