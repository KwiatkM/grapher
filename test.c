#include "inout.h"
#include "dijkstra.h"
#include "bfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_GRAPH_DIM 500

// tablice do dijkstry
int *poprzednik;
double *odleglosc;
char *odwiedzono;

// tablica do BFS
char *tab_odw;

int main(int argc, char **argv)
{
    int liczba_grafow = 10;
    int liczba_sciezek = 10;
    int i = 0;
    char *file_in = NULL;
    char *file_out = "file_out_test";
    char tryb = 's';

    int x = 10, y = 10;
    double szansa = 1.0;
    wierzcholek_t *graf;

    if (argc > 1)
    {
        if (argv[1][0] != '-')
        {
            printf("niepoprawny argument wywolania: %s\n", argv[1]);
            return 1;
        }

        if (argv[1][1] == 'p')
        {
            tryb = 'p';
            if (argc > 2)
                file_in = argv[2];
            if (argc > 3)
                file_out = argv[3];
            if (argc > 4)
                liczba_sciezek = atoi(argv[4]);
        }

        if (argv[1][1] == 's')
        {
            if (argc > 2)
                file_out = argv[2];
            if (argc > 3)
                liczba_grafow = atoi(argv[3]);
        }
    }

    printf("liczba grafow: %d\n", liczba_grafow);
    printf("liczba sciezek: %d\n", liczba_sciezek);
    printf("file in: %s\n", file_in);
    printf("file out: %s\n", file_out);

    if (tryb == 'p') // tryb szukania sciezek w jednym grafie
    {
        if (file_in == NULL)
        {
            fprintf(stderr, "%s: nie podano pliku z grafem\n", argv[0]);
            return 1;
        }

        FILE *in = fopen(file_in, "r");
        if (in == NULL)
        {
            fprintf(stderr, "%s: nie udalo sie otworzyc pliku %s\n", argv[0], file_in);
            return 1;
        }

        fscanf(in, "%d %d\n", &x, &y);

        graf = kontenerInit(x, y);
        if (graf == NULL)
        {
            fprintf(stderr, "%s: nie udalo sie utworzyc struktury przechowujacej graf\n", argv[0]);
            return 1;
        }

        if (wczytaj_graf(graf, x, y, in) == 1)
        {
            fclose(in);
            fprintf(stderr, "%s: plik %s zawiera niepoprawnie zapisany graf\n", argv[0], file_in);
            return 1;
        }
        fclose(in);

        int w_start;
        int w_konc;

        FILE *out = fopen(file_out, "w");
        if (out == NULL)
        {
            fprintf(stderr, "%s: nie usalo sie otowrzyc pliku %s\n", argv[0], file_out);
            return 1;
        }
        fprintf(out, "Rozmiar grafu: %d x %d\n", x, y);
        fprintf(out, "Liczba sciezek: %d\n\n", liczba_sciezek);

        dijTabInit(x, y);
        srand(time(NULL));
        for (i = 0; i < liczba_sciezek; i++)
        {
            w_start = rand() % (x * y);
            w_konc = rand() % (x * y);

            dijkstra(graf, x, y, w_start, w_konc);

            fprintf(out, "sciezka miedzy wierzcholkami %d i %d:\n", w_start, w_konc);
            wypisz_sciezke(out, w_start, w_konc);
            fprintf(out, "\n\n");

            dijTabReset(x, y);
        }
        fclose(out);

        dijTabFree();
        free(graf);
    }
    if (tryb == 's') // tryb generowania grafów i sprawdzanie ich spójności
    {

        FILE *out = fopen(file_out, "w");
        if (out == NULL)
        {
            fprintf(stderr, "%s: nie usalo sie otowrzyc pliku %s\n", argv[0], file_out);
            return 1;
        }

        for (i = 0; i < liczba_grafow; i++)
        {
            x = rand() % MAX_GRAPH_DIM;
            y = rand() % MAX_GRAPH_DIM;
            szansa = (double)rand()/RAND_MAX;

            graf = kontenerInit(x, y);
            gen_graf(graf, x, y, 0, 10, szansa);
            if (graf == NULL)
            {
                fprintf(stderr, "%s: nie udalo sie utworzyc struktury przechowujacej graf nr %d\n", argv[0], i + 1);
                return 1;
            }
            bfsTabInit(x,y);
            bfs(graf,x,y,0);

            fprintf(out, "rozmiary grafu nr %d: %d x %d\n",i,x,y);
            fprintf(out, "szansa na krawedz: %f\n", szansa);
            fprintf(out, "czy spojny: %s\n\n", czySpojny(x,y) == 1 ? "tak" : "nie");

            BFSTabFree;
            free(graf);
        }
    }

    printf("koniec\n");
    return 0;
}