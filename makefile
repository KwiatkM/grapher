grapher: main.o inout.o dijkstra.o bfs.o
	cc -o grapher main.o inout.o dijkstra.o bfs.o 

main.o: main.c inout.o dijkstra.o bfs.o
	cc main.c inout.o dijkstra.o bfs.o

inout.o: inout.c inout.h
	cc -c inout.c inout.h

dijkstra.o: dijkstra.c dijkstra.h
	cc -c dijkstra.c dijkstra.h

bfs.o: bfs.h bfs.c
	cc -c bfs.h bfs.c

clean:
	rm *.o grapher