CC=gcc
CFLAGS=-I. -std=c11 -pthread

all: tcpclient tcpserver udpclient udpserver server client

tcpclient: tcpclient.c
	$(CC) -o tcpclient tcpclient.c $(CFLAGS)

tcpserver: tcpserver.c
	$(CC) -o tcpserver tcpserver.c $(CFLAGS)

udpclient: udpclient.c
	$(CC) -o udpclient udpclient.c $(CFLAGS)

udpserver: udpserver.c
	$(CC) -o udpserver udpserver.c $(CFLAGS)

server: server.c
	$(CC) -o server server.c $(CFLAGS)

client: client.c
	$(CC) -o client client.c $(CFLAGS)

clean:
	rm tcpserver tcpclient udpclient udpserver server client