#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "inout.h"


wierzcholek_t * kontenerInit (int x, int y){
    wierzcholek_t * tmp = malloc (x * y * sizeof (wierzcholek_t));
    if (tmp == NULL) return NULL;
    int j;
    for (j = 0; j < x*y; j++){
        (tmp + j)->down = -1.1;
        (tmp + j)->right = -1.1;
    }
    return tmp;
}

int gen_graf(wierzcholek_t * graf, int x, int y, double waga_od, double waga_do, double szansa){
    srand(time(NULL));
    int i;
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
}

int wczytaj_graf (wierzcholek_t * graf, int x, int y, FILE * in){
    int i, j;
    char buf[128];

    //tymczasowe wartości do przechowywania danych z linijek pliku
    int a[4] = { -1 }; //numery wierzchołków
    double aa[4] = { -1.1 };    // wartości krawędzi
    int b;

    for (i = 0; i < x * y; i ++){
    fgets(buf,128,in);
    b = sscanf(buf, " %d :%lf  %d :%lf  %d :%lf  %d :%lf ", &a[0], &aa[0], &a[1], &aa[1], &a[2], &aa[2], &a[3], &aa[3]);
    
        for(j = 0; j < b/2; j++){ 
            if(a[j] == -1) continue; // nie wiem czy nie lepszy będzie break
            if( a[j] == i -1){
                // jeżeli wierzchołek jest z lewej    
                if(i%y == 0) return 1;
                if((graf+a[j])->right != aa[j]) return 1;
            } 
            else if( a[j] == i - y){
                // jeżeli wierzchołek jest u góry
                if(a[j]<0) return 1;
                if((graf+a[j])->down != aa[j]) return 1;
            } 
            // dla wierzchołka u góry i po lewo sprawdzamy jedynie, czy wagi się zgadzają

            else if( a[j] == i + 1){
                // jeżeli wierzchołek jest z prawej
                if((i+1)%y == 0) return 1;
                (graf+i)->right = aa[j];
            } 
            else if( a[j] == i + y){
                // jeżeli wierzchołek jest na dole  
                if(i >= (x*y)-y) return 1;
                (graf+i)->down = aa[j];
            } 
            else {
                return 1;
                }    // jeżeli nie ma połączenia z wierzchołkiem

        }

    }

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
        if((i-y)>=0){ // jeżeli w ogóle istnieje
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
