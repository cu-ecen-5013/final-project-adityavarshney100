#define MY_PORT ("9000")
#define BACKLOG (10)
#define MAX_SIZE (1024)

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

FILE *fp;
char *buffer;
int sockfd,new_fd;
struct addrinfo *res;
bool caught_sigint = false;
bool caught_sigterm = false;

static void signal_handler ( int signal_number )
{
    int errno_saved = errno;
    if ( signal_number == SIGINT || signal_number == SIGTERM)
	{
		caught_sigint = true;
	}
    errno = errno_saved;
}

int main(int argc, char *argv[])
{
	openlog(NULL,0,LOG_USER);
	struct addrinfo hints, *res, *p;
	int status;

	/*******************/
	//SIGNAL Handler initialisation
	struct sigaction new_action;
	    bool success = true;
	    memset(&new_action,0,sizeof(struct sigaction));
	    new_action.sa_handler=signal_handler;
	    if( sigaction(SIGTERM, &new_action, NULL) != 0 ) {
		perror("Failed");
		success = false;
	    }
	    if( sigaction(SIGINT, &new_action, NULL) ) {
		perror("Failed");
		success = false;
	    }
	/*********************/

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((status = getaddrinfo(NULL, "9000", &hints, &res)) != 0) 
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return -1;
	}
	syslog(LOG_INFO,"Server Socket crearted\n");

	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if(bind(sockfd, res->ai_addr, res->ai_addrlen) == -1)
	{
		close(sockfd);
		//printf("Binding failed\n");
		return -1;
	}
	syslog(LOG_INFO,"Binding done...\n");

	if (argc > 1 )
	{ 
		if(!strcmp(argv[1],"-d"))
		{
			syslog(LOG_INFO,"Accepted as daemon\n");
			if(daemon(0,sockfd) != 0)
			{
				syslog(LOG_INFO,"Error in daemon");
				exit(-1);
			}
		}
	}
	listen(sockfd, 10);
	syslog(LOG_INFO,"Listening....\n");

	struct sockaddr_storage their_addr; // connector's address information
	socklen_t sin_size = sizeof their_addr;

	fp = fopen("/var/tmp/aesdsocketdata","w+");
	int num_bytes=0;
	buffer = (char*)malloc(MAX_SIZE*sizeof(char));

	while(1)
	{
		memset(buffer,0,MAX_SIZE);
		long file_size;

		new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
		if (new_fd == -1)
		{
			break;
		}
		if(caught_sigint)
		{
			printf("caught sigint");
			break;
		}

		char *temp_variable;
		temp_variable = 0;
		long string_length=0;
		
		do
		{
			num_bytes=recv(new_fd,(buffer+string_length),sizeof(char),0);
			string_length+=num_bytes;
		}while(*(buffer+string_length - 1) != '\n');

		syslog(LOG_INFO,"Writing to file...\n");
		fputs(buffer,fp);

		fseek(fp, 0L, SEEK_END);	//Getting the size of the file
		file_size = ftell(fp);
		fseek(fp,0L,SEEK_SET);

		num_bytes=fread(buffer,sizeof(char),file_size,fp);
		syslog(LOG_INFO,"Reading from file...%d\n",num_bytes);

		int i=send(new_fd,buffer,num_bytes,0);
		syslog(LOG_INFO,"Sending...%d\n",i);
		

}
	printf("Exit gracefully\n");
	remove("/var/tmp/aesdsocketdata");	//Deleting the file
	free(buffer);
	fclose(fp);
	close(new_fd);
	close(sockfd);
	freeaddrinfo(res); 			// free the linked list	

	return 0;
}
