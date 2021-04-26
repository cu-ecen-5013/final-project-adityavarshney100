ifeq ($(CC),)
	CC = $(CROSS_COMPILE)gcc
endif
ifeq ($(CFLAGS),)
	CFLAGS = -g -Wall -Werror
endif
ifeq ($(LDFLAGS),)
	LDFLAGS = -pthread -lrt
endif

all: aesdclient aesdserver client_test server_test uart_test reader_test writer_test final_server final_client

aesdclient: Test_code/Socket_test_code/aesdclient.c
	$(CC) $(CFLAGS) Test_code/Socket_test_code/aesdclient.c -o aesdclient $(LDFLAGS)

aesdserver: Test_code/Socket_test_code/aesdserver.c
	$(CC) $(CFLAGS) Test_code/Socket_test_code/aesdserver.c -o aesdserver $(LDFLAGS)

client_test: Test_code/Socket_test_code/client_test.c
	$(CC) $(CFLAGS) Test_code/Socket_test_code/client_test.c -o client_test $(LDFLAGS)

server_test: Test_code/Socket_test_code/server_test.c
	$(CC) $(CFLAGS) Test_code/Socket_test_code/server_test.c -o server_test $(LDFLAGS)

uart_test: Test_code/Uart_loopback_test_code/uart_test.c
	$(CC) $(CFLAGS) Test_code/Uart_loopback_test_code/uart_test.c -o uart_test $(LDFLAGS)

reader_test: Test_code/Message_queue_test_code/reader_test.c
	$(CC) $(CFLAGS) Test_code/Message_queue_test_code/reader_test.c -o reader_test $(LDFLAGS)

writer_test: Test_code/Message_queue_test_code/writer_test.c
	$(CC) $(CFLAGS) Test_code/Message_queue_test_code/writer_test.c -o writer_test $(LDFLAGS)

final_server: Test_code/Integrated_code/server_test.c Test_code/Integrated_code/gpio.c
	$(CC) $(CFLAGS) Test_code/Integrated_code/server_test.c -o final_server $(LDFLAGS)

final_client: Test_code/Integrated_code/client_test.c
	$(CC) $(CFLAGS) Test_code/Integrated_code/client_test.c -o final_client $(LDFLAGS)

clean:
	rm -f *.o aesdclient aesdserver client_test server_test uart_test reader_test writer_test final_server final_client



