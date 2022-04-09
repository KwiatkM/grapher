#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"


int dijTabInit (int x, int y){
poprzednik = malloc(x * y * sizeof(int));
odleglosc = malloc(x * y * sizeof(double));
odwiedzono = malloc(x * y * sizeof(char));
if ( poprzednik == NULL || odleglosc == NULL || odwiedzono == NULL) return 1;
int i; 
for (i = 0; i < x*y; i++){
    poprzednik[i] = -1;
    odleglosc[i] = 99999999999.9; // trzeba ograniczyć maksymalną wagę do tej wartośći
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

int dijkstra ( int w_start ){

}

int dijTabFree( void ){
    free(poprzednik);
    free(odleglosc);
    free(odwiedzono);
    return 0;
}