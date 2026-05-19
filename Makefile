
all: exec

main.o: main.c plateau.h
  gcc -c main.c -o main.o

plateau.o: plateau.c plateau.h
  gcc -c plateau.c -o plateau.o

exec: main.o plateau.o
  gcc main.o plateau.o -o exec

clean: 
  rm -f *.o
  rm exec
