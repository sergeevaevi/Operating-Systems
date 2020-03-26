SRC = main.c

main.o: main.c
	gcc -c -o main.o $(SRC)

f1.o: f1.c
	gcc -c -o f1.o f1.c

f2.o: f2.c
	gcc -c -o f2.o f2.c

hello: main.o f1.o f2.o
	gcc -o hello main.o f1.o f2.o -lm

