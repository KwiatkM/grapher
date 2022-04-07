#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "inout.h"

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
                if(optarg = NULL) //jesli nei podamy -t to waga_do = 100.0
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
    for(i=0; i<wymiar_x; i++){
        graf[i] = malloc(wymiar_y * sizeof(*graf[i]));
    }
    

    createGraph(graf, wymiar_x, wymiar_y, waga_od, waga_do, szansa);  //wywolujemy funkcje tworzaca graf(nadajaca losowe przejcia i losowe wagi)
    
    saveGraph(graf, wymiar_x, wymiar_y, file_out_graph);    //wywolujemy funkcje zapisujaca stworzony graf do pliku

    fclose(file_out_graph);    

    for(i=0; i<wymiar_x; i++){          /*zwalniamy pamiec dla grafu*/
        free(graf[i]);  
    }
    free(graf);
    return 0;
}