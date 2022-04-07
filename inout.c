#include <stdio.h>
#include <stdlib.h>
#include "inout.h"

wierzcholek_t * kontenerInit (int x, int y){
    wierzcholek_t * tmp = malloc (x * y * sizeof (wierzcholek_t));
    int j;
    for (j = 0; j < x*y; j++){
        (tmp + j)->down = -1.1;
        (tmp + j)->right = -1.1;
    }
    return tmp;
}

int krawedzDodaj (int x, int y, int nr_w_1, int nr_w_2, double wartosc){
    
}

int wagiWypisz (int x, int y, int nr_w, char * out){

}

void wypisz_graf(wierzcholek_t * graf, int x, int y){
    int i;
    for (i=0; i < x*y; i++){
        printf("wierzcholek %d: prawo: %lf dol: %lf\n",i, (graf + i)->right, (graf + i)->down);
    }
}


int zapiszGraf (wierzcholek_t * graf, int x, int y, FILE * out){
    
    fprintf(out, "%d %d\n", x, y);
    
    int i;
    for(i=0; i < x*y; i++){
        fprintf(out, "\t");
        
        // krawędź górna
        if((i-y)>=0){
            fprintf(out, " %d :%0.16f ", i-y, (graf+i-y)->down);
        }

        // krawędź prawa
        if((i+1)%y != 0){
            fprintf(out, " %d :%0.16f ", i+1, (graf+i)->right);
        }

        // krawędź dolna
        if(i < (x*y)-y){
            fprintf(out, " %d :%0.16f ", i+y, (graf+i)->down);
        }

        // krawędź lewa
        if(i%y != 0){
            fprintf(out, " %d :%0.16f ", i-1, (graf+i-1)->right);
        }

        fprintf(out, "\n");
    }
    return 0;
}

