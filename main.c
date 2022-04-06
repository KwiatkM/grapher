#include "inout.h"
#include "dijkstra.h"
#include "bfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

int main(int argc, char** argv){

    char * file_out_graph = "file_out_graph";
    char * file_in = NULL;
    char * file_out_path = "stdout";
    int x = 100, y = 100, wierzcholek_1 = 0, wierzcholek_2 = 1;
    double waga_od = 0.0, waga_do = 100.0, szansa = 1.0;

    int i = 1;
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

    return 0;
}

