# Makefile - projet CY-Connect
# Attention : les lignes de commandes commencent par une TABULATION

CC = gcc
CFLAGS = -Wall

all: exec

# $< = la 1ere dependance (le .c)
# $@ = la cible (le .o)
main.o: main.c board.h save.h
	$(CC) $(CFLAGS) -c $< -o $@

board.o: board.c board.h
	$(CC) $(CFLAGS) -c $< -o $@

save.o: save.c save.h board.h
	$(CC) $(CFLAGS) -c $< -o $@

# $^ = liste de toutes les dependances
exec: main.o board.o save.o
	$(CC) $^ -o $@

clean:
	rm -f *.o exec

.PHONY: all clean
