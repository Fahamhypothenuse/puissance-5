CC = gcc
CFLAGS = -Wall

all: exec

main.o: main.c board.h save.h
	$(CC) $(CFLAGS) -c $< -o $@

board.o: board.c board.h
	$(CC) $(CFLAGS) -c $< -o $@

save.o: save.c save.h board.h
	$(CC) $(CFLAGS) -c $< -o $@


exec: main.o board.o save.o
	$(CC) $^ -o $@

clean:
	rm -f *.o exec

.PHONY: all clean
