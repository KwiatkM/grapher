grapher: main.c inout.o dijkstra.o bfs.o
	gcc -o grapher main.c inout.o dijkstra.o bfs.o 

inout.o: inout.c inout.h
	gcc -c inout.c 

dijkstra.o: dijkstra.c dijkstra.h
	gcc -c dijkstra.c

bfs.o: bfs.h bfs.c
	gcc -c bfs.c

debug: main.c inout.o dijkstra.o bfs.o
	gcc -o grapher_D main.c inout.o dijkstra.o bfs.o -DDEBUG

grapher_test: test.c inout.o dijkstra.o bfs.o
	gcc -o grapher_test test.c inout.o dijkstra.o bfs.o 

