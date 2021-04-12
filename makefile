ifeq ($(CC),)
	CC = $(CROSS_COMPILE)gcc
endif
ifeq ($(CFLAGS),)
	CFLAGS = -g -Wall -Werror
endif
ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt
endif

all: aesdclient aesdserver client_test server_test

aesdclient: aesdclient.c
	$(CC) $(CFLAGS) ${INCLUDES} ${OBJS} aesdclient.c -o aesdclient

aesdserver: aesdserver.c
	$(CC) $(CFLAGS) ${INCLUDES} ${OBJS} aesdserver.c -o aesdserver

client_test: client_test.c
	$(CC) $(CFLAGS) ${INCLUDES} ${OBJS} client_test.c -o client_test

server_test: server_test.c
	$(CC) $(CFLAGS) ${INCLUDES} ${OBJS} server_test.c -o server_test

clean:
	rm -f *.o aesdclient
	rm -f *.o aesdserver
	rm -f *.o client_test
	rm -f *.o server_test


