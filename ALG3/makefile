#compilador da avl

myavl: avl.o APIavl.o
	gcc -o myavl avl.o APIavl.o

avl.o: avl.c APIavl.h
	gcc -o avl.o avl.c -c -Wall

APIavl.o: APIavl.c APIavl.h
	gcc -o APIavl.o APIavl.c -c -Wall

clean:
	rm *.o
