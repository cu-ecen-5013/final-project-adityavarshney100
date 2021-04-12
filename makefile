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
	$(CC) $(CFLAGS) aesdclient.c -o aesdclient $(LDFLAGS)

aesdserver: aesdserver.c
	$(CC) $(CFLAGS) aesdserver.c -o aesdserver $(LDFLAGS)

client_test: client_test.c
	$(CC) $(CFLAGS) client_test.c -o client_test $(LDFLAGS)

server_test: server_test.c
	$(CC) $(CFLAGS) server_test.c -o server_test $(LDFLAGS)

clean:
	rm -f *.o aesdclient
	rm -f *.o aesdserver
	rm -f *.o client_test
	rm -f *.o server_test


