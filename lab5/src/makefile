CC=gcc
CFLAGS=-I. -std=c99 -pthread

all: mutex no_mutex factorial

again: clean factorial

mutex: mutex.c
	$(CC) -o mutex mutex.c $(CFLAGS)

no_mutex: no_mutex.c
	$(CC) -o no_mutex no_mutex.c $(CFLAGS)

factorial: factorial.c
	$(CC) -o factorial factorial.c $(CFLAGS)

clean :
	rm mutex no_mutex factorial