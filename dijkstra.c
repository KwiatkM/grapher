#include <stdio.h>
#include <stdlib.h>
#include "inout.h"
#include "dijkstra.h"


#define INFINITY 99999999999.9

int dijTabInit (int x, int y){
poprzednik = malloc(x * y * sizeof(int));
odleglosc = malloc(x * y * sizeof(double));
odwiedzono = malloc(x * y * sizeof(char));
if ( poprzednik == NULL || odleglosc == NULL || odwiedzono == NULL) return 1;
int i; 
for (i = 0; i < x*y; i++){
    poprzednik[i] = -1;
    odleglosc[i] = INFINITY; // trzeba ograniczyć maksymalną wagę do tej wartośći
    odwiedzono[i]= '0';
}
return 0;
}

int pKolejkaDodaj (pkolejka_t ** kolejka,int nr_wierz ){
    pkolejka_t * tmp = malloc(sizeof(pkolejka_t));
    tmp->nr_wierz = nr_wierz;
    tmp->next = NULL;
    tmp->prev = NULL;

    if( *kolejka == NULL){
        *kolejka = tmp;
        return 0;
    }

    pkolejka_t * head = *kolejka;
    while( head != NULL){
        if( odleglosc[nr_wierz] < odleglosc[head->nr_wierz]){ 
            tmp->next = head;
            tmp->prev = head->prev;                         
            if(head->prev != NULL) head->prev->next = tmp;
            head->prev = tmp;
            if( odleglosc[(*kolejka)->nr_wierz] > odleglosc[tmp->nr_wierz]) *kolejka = tmp; //
                                                             // gdy wkładany element jest mniejszy od elementu na
            return 0;                                        // początku kolejki to kolejka będzie się zaczynać 
                                                             // właśnie od tego elementu
        }
        if( head->next == NULL){
            head->next = tmp;
            tmp->prev = head;
            return 0;
        }
        head = head->next;
    }
}

int pKolejkaZdejmij ( pkolejka_t ** kolejka ){
    if(*kolejka == NULL) return -1;
    int tmp = (*kolejka)->nr_wierz;
    pkolejka_t * tmp_k = *kolejka;
    *kolejka = (*kolejka)->next;
    if(*kolejka != NULL) (*kolejka)->prev = NULL;
    free(tmp_k);
    return tmp;
    
}

int pKolejkaWypisz ( pkolejka_t * kolejka  ){
    if (kolejka == NULL) return -1;
    while ( kolejka != NULL){
        printf("%d - ", kolejka->nr_wierz);
        kolejka = kolejka->next;
    }
    printf("\n");
    return 0;
}

int pKolejkaAktualizuj (pkolejka_t ** kolejka, int nr_w){
// długość drogi wierzchołków może się tylko zmniejszać
pkolejka_t * head = *kolejka;

// znajdujemy dany wierzchołek w kolejce
while(head != NULL){
    if(head->nr_wierz == nr_w) break;
    head = head->next;
}

if (head == NULL) return -1;

// usuwamy wierzchołek z kolejki
pkolejka_t * w = head;

// sprawdzenie, czy wierzchołek nie jest na początku kolejki lub czy
// w ogóle potrzebuje przestawienia
if ( head->prev == NULL) return 0;

if(odleglosc[head->prev->nr_wierz] < odleglosc[head->nr_wierz]) return 0;

    // sprawdzenie czy za elementem kolejki są w ogóle jakieś inne elementy
if( head->next == NULL){
     head->prev->next = NULL;
     head = head->prev;
     w->prev = NULL;
}
else{
     head = head->prev;          //odłączenie elementu w od kolejki
    head->next = w->next;   
    head->next->prev = head;
     w->next = NULL;
    w->prev = NULL;
}

// wskaźnik w to ten odłączony element

while(head->prev != NULL){
    // dołączenie z powrotem do kolejki idąc w drugą stronę
    if( odleglosc[head->prev->nr_wierz] < odleglosc[w->nr_wierz]){
        head->prev->next = w;
        w->next = head;
        w->prev = head->prev;
        head->prev = w;
        return 0;
    }
    head = head->prev;
}
    // gdy wszystkie elementy kolejki są większe od wartości w strukturze w
    // dołanczamy w na sam początek kolejki
    head->prev = w;
    w->next = head;
    *kolejka = w;
    return 0;

}

int dijkstra ( wierzcholek_t * graf,  int w_start, int x, int y ){

    pkolejka_t * kolejka = NULL;
    dijTabInit(x,y);
    odleglosc[w_start] = 0.0;
    pKolejkaDodaj(&kolejka, w_start);

    int u; // analizowany wierzchołek
    while(kolejka != NULL){
        u = pKolejkaZdejmij(&kolejka);
        odwiedzono[u] = '1';

        double tmp;
        // wierzchołek po lewo
        if(u%y != 0){ // jeżeli u ma wierzchołek po lewo
            if((graf+u-1)->right > 0){ // jeżli istnieje przejście
                if(odwiedzono[u-1] == '0'){ // jeżeli u nie był odwiedzony
                    if(odleglosc[u-1] > odleglosc[u] + (graf+u-1)->right ){
                        tmp = odleglosc[u-1]; // aby sprawdzić czy był wcześniej dodany do kolejki
                        odleglosc[u-1] = odleglosc[u] + (graf+u-1)->right;
                        poprzednik[u-1] = u;
                        if(tmp = INFINITY) pKolejkaDodaj (&kolejka, u-1);
                        else pKolejkaAktualizuj (&kolejka, u-1);
                    }
                }
            }
        }

        // wierzchołek u góry
        if((u-y)>=0){
            if((graf+u-y)->down > 0){
                if(odwiedzono[u-y] == '0'){
                    if(odleglosc[u-y] > odleglosc[u] + (graf+u-y)->down){
                        tmp = odleglosc[u-y];
                        odleglosc[u-y] = odleglosc[u] + (graf+u-y)->down;
                        poprzednik[u-y] = u;
                        if(tmp = INFINITY) pKolejkaDodaj (&kolejka, u-y);
                        else pKolejkaAktualizuj (&kolejka, u-y);
                    }
                }
            }
        }

        //wierzchołek na prawo
        if((u+1)%y != 0){ // jeżeli u ma wierzchołek po prawo
            if((graf+u)->right > 0){ // jeżli istnieje przejście
                if(odwiedzono[u+1] == '0'){ // jeżeli u nie był odwiedzony
                    if(odleglosc[u+1] > odleglosc[u] + (graf+u)->right ){
                        tmp = odleglosc[u+1]; // aby sprawdzić czy był wcześniej dodany do kolejki
                        odleglosc[u+1] = odleglosc[u] + (graf+u)->right;
                        poprzednik[u+1] = u;
                        if(tmp = INFINITY) pKolejkaDodaj (&kolejka, u+1);
                        else pKolejkaAktualizuj (&kolejka, u+1);
                    }
                }
            }
        }

        //wierzchołek na dole
        if(u < (x*y)-y){
            if((graf+u)->down > 0){
                if(odwiedzono[u+y] == '0'){
                    if(odleglosc[u+y] > odleglosc[u] + (graf+u)->down){
                        tmp = odleglosc[u+y];
                        odleglosc[u+y] = odleglosc[u] + (graf+u)->down;
                        poprzednik[u+y] = u;
                        if(tmp = INFINITY) pKolejkaDodaj (&kolejka, u+y);
                        else pKolejkaAktualizuj (&kolejka, u+y);
                    }
                }
            }
        }

    }


}

int wypiszTablice(int x, int y){
    int i;
    for (i = 0; i < x*y; i++ ){
        printf("wierzcholek %d: odw: %c, odl:%lf, poprz: %d\n", i, odwiedzono[i], odleglosc[i], poprzednik[i]);
    }
    return 0;
    
}

int dijTabFree( void ){
    free(poprzednik);
    free(odleglosc);
    free(odwiedzono);
    return 0;
}