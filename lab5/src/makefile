CC=gcc
CFLAGS=-I. -std=c99

all: mutex no_mutex

mutex: mutex.c
	$(CC) -o mutex mutex.c $(CFLAGS)

no_mutex: no_mutex.c
	$(CC) -o no_mutex no_mutex.c

clean :
	rm mutex no_mutex
