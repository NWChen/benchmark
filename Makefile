CC=gcc -std=c99
CFLAGS=-I.

benchmark: benchmark.o
	$(CC) -o benchmark benchmark.o

.PHONY: clean

clean:
	rm -f benchmark *.o
