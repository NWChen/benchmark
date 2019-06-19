CC=gcc
CFLAGS=-I.

primes: primes.o
	$(CC) -o primes primes.o

.PHONY: clean

clean:
	rm -f primes *.o
