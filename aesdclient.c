#define MY_PORT ("9000")
#define BACKLOG (10)
#define BUFFER_SIZE 1000

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <errno.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include "queue.h"
#include <sys/wait.h>
#include <sys/time.h>

FILE *fp;
int sockfd,new_fd;
struct addrinfo *res;
volatile int caught_sigint = false;

bool caught_sigalarm = false;
pthread_mutex_t lock;

pthread_t time_id;
int i=0;
int lock_unlock_status=0;

bool thread_complete_thread=0;



int main(int argc, char *argv[])
{

	openlog(NULL,0,LOG_USER);
	struct addrinfo hints, *res, *temp;
	int status,i=0,size;


	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(argv[1], MY_PORT , &hints, &res)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		syslog(LOG_INFO,"Server Socket failed\n");
		return -1;
	}
	syslog(LOG_INFO,"Server Socket crearted\n");

/*****************************************************/
//Leveraged the for loop condition from https://github.com/cu-ecen-5013/final-project-sarayumanagoli

	for(temp = servinfo; temp != NULL; temp = temp->ai_next)
	{
		if(sockfd = socket(temp->ai_family, temp->ai_socktype, temp->ai_protocol)==-1);
			continue;
		if(connect(sockfd,tmep->ai_addr,p->ai_addrlen)==-1)
			continue;
		break;
	}

	inet_ntop(temp->ai_family, get_in_addr((struct sockaddr *)temp->ai_addr), s, sizeof s);
	printf("Client connected to %s\n", s);
/*****************************************************/
	
	freeaddrinfo(res);
	
	while(i<10)
	{
		strcpy(buf,"Hi from the client side\n");
		size = recv(sockfd,buf,BUFFER_SIZE-1,0);
		if(size==-1)
		{
			perror("recv");
			exit(1);
		}
		buf[size] = '\0';

		printf("client: received: %s\n",buf);
	}

	close(sockfd);


	return(0);
}
