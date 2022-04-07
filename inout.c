#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "inout.h"

void createGraph(wierzcholek_t **graf, int wymiar_x, int wymiar_y, double waga_od, double waga_do, double szansa){
    double los_przejscie, los_waga;
    srand(time(NULL));

    for(x=0; x<wymiar_x; x++){               //iterujemy po calym grafie
        for(y=0; y<wymiar_y; y++){
            if(y == wymiar_y - 1 && x != wymiar_x - 1){        //jesli zolty wierzcholek
                graf[x][y].right = -1.1;                      //na prawo nie ma przejscia, wiec -1.1
                los_przejscie = (double)rand()/RAND_MAX  * (1.0 - 0.0) + 0.0;       //losujemy double z zakresu 0.0 - 1.0
                if(los_przejscie <= szansa){       //czyli jest przejscie w tym kierunku
                    los_waga = (double)rand()/RAND_MAX * (waga_do - waga_od) + waga_od;    //jest przejscie, wiec losujemy wage dla tego przejscia
                    graf[x][y].down = los_waga;
                }
                else
                    graf[x][y].down = -1.1;         //jesli nie ma przejscia w tym kierunku to -1.1
                continue;
            }
            if(x == wymiar_x - 1 && y != wymiar_y - 1){     //jesli zielony wierzcholek
                los_przejscie = (double)rand()/RAND_MAX  * (1.0 - 0.0) + 0.0;
                if(los_przejscie <= szansa){      
                    los_waga = (double)rand()/RAND_MAX  * (waga_do - waga_od) + waga_od;
                    graf[x][y].right = los_waga;
                }
                else
                    graf[x][y].right = -1.1;
                graf[x][y].down = -1.1;
                continue;
            }
            if(x == wymiar_x - 1 && y == wymiar_y - 1){     //jesli niebieski wierzcholek
                graf[x][y].right = -1.1;
                graf[x][y].down = -1.1;
                continue;
            }
            else{                                    //wszystkie pozostale wierzcholki(fioletowe)
                los_przejscie = (double)rand()/RAND_MAX  * (1.0 - 0.0) + 0.0;
                if(los_przejscie <= szansa){
                    los_waga = (double)rand()/RAND_MAX  * (waga_do - waga_od) + waga_od;
                    graf[x][y].right = los_waga;
                }
                else
                    graf[x][y].right = -1.1;

                los_przejscie = (double)rand()/RAND_MAX  * (1.0 - 0.0) + 0.0;
                if(los_przejscie <= szansa){
                    los_waga = (double)rand()/RAND_MAX  * (waga_do - waga_od) + waga_od;
                    graf[x][y].down = los_waga;
                }
                else
                    graf[x][y].down = -1.1;
                continue;
            }
        }
    }
}
void saveGraph(wierzcholek_t **graf, int wymiar_x, int wymiar_y, FILE * file_out_graph){
    fprintf(file_out_graph, "%d %d\n", wymiar_x, wymiar_y);   //<--- zapisujemy najpierw do pliku wymiary grafu
    for(x=0; x<wymiar_x; x++){              //<--- i teraz zapisujemy do pliku caly graf w odpowiednim formacie
        for(y=0; y<wymiar_y; y++){
            if(x == 0 && y == 0){           //<--- wierzcholek zolty(nie sprawdzamy na gorze i na lewo)
                if(graf[x][y].right != -1.1){       //<--- sprawdzamy wage right
                    fprintf(file_out_graph, "%d :%lf ", x * wymiar_y + (y+1), graf[x][y].right);
                }   
                if(graf[x][y].down != -1.1){        //<--- nastepnie sprawdzamy wage down
                    fprintf(file_out_graph, "%d :%lf ", (x+1) * wymiar_y + y, graf[x][y].down);
                }
                fprintf(file_out_graph, "\n"); // <--- przechodzimy do kolejnej linii(wierzcholka)
                continue;
            }
            if(x == 0 && y != 0){       //<--- wierzcholek zielony(nie sprawdzamy na gorze)
                if(graf[x][y - 1].right != -1.1 ){  //<--- sprawdzamy wage "left" poprzez sprawdzenie dla wierz. lewego jaka ma wage right
                    fprintf(file_out_graph, "%d :%lf ", x * wymiar_y + (y-1), graf[x][y - 1].right);
                }
                if(graf[x][y].right != -1.1){       //<--- sprawdzamy wage right
                    fprintf(file_out_graph, "%d :%lf ", x * wymiar_y + (y+1), graf[x][y].right);
                }
                if(graf[x][y].down != -1.1){       //<--- sprawdzamy wage down
                    fprintf(file_out_graph, "%d :%lf ", (x+1) * wymiar_y + y, graf[x][y].down);
                }
                fprintf(file_out_graph, "\n"); // <--- przechodzimy do kolejnej linii(wierzcholka)
                continue;
            }
            if(x != 0 && y == 0){       //<--- wierzcholek niebieski(nie sprawdzamy na lewo)
                if(graf[x - 1][y].down != -1.1){    //<--- sprawdzamy wage "up" poprzez sprawdzenie dla wierz. gornego jaka ma wage down
                    fprintf(file_out_graph, "%d :%lf ", (x-1) * wymiar_y + y, graf[x - 1][y].down);
                }
                if(graf[x][y].right != -1.1){       //<--- sprawdzamy wage right
                    fprintf(file_out_graph, "%d :%lf ", x * wymiar_y + (y+1), graf[x][y].right);
                }
                if(graf[x][y].down != -1.1){       //<--- sprawdzamy wage down
                    fprintf(file_out_graph, "%d :%lf ", (x+1) * wymiar_y + y, graf[x][y].down);
                }
                fprintf(file_out_graph, "\n"); // <--- przechodzimy do kolejnej linii(wierzcholka)
                continue;
            }
            else{       //<--- wszystkie pozostale wierzcholki(fioletowe)
                if(graf[x - 1][y].down != -1.1){    //<--- sprawdzamy wage "up" poprzez sprawdzenie dla wierz. gornego jaka ma wage down
                    fprintf(file_out_graph, "%d :%lf ", (x-1) * wymiar_y + y, graf[x - 1][y].down);
                }
                if(graf[x][y - 1].right != -1.1){  //<--- sprawdzamy wage "left" poprzez sprawdzenie dla wierz. lewego jaka ma wage right
                    fprintf(file_out_graph, "%d :%lf ", x * wymiar_y + (y-1), graf[x][y - 1].right);
                }
                if(graf[x][y].right != -1.1){       //<--- sprawdzamy wage right
                    fprintf(file_out_graph, "%d :%lf ", x * wymiar_y + (y+1), graf[x][y].right);
                }
                if(graf[x][y].down != -1.1){       //<--- sprawdzamy wage down
                    fprintf(file_out_graph, "%d :%lf ", (x+1) * wymiar_y + y, graf[x][y].down);
                }
                fprintf(file_out_graph, "\n"); // <--- przechodzimy do kolejnej linii(wierzcholka)
                continue;
            }
        }
    }
}
