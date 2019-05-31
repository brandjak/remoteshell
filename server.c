#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 9000

void* run_shell(void* data);

int main()
{
	int sfd;
	int sockopt=1;

	struct sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Couldn't open the socket");
		exit(-1);
	}
	setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, (char*) &sockopt, sizeof(sockopt));

	if(bind(sfd, (struct sockaddr*) &serveraddr, sizeof(serveraddr))<0)
	{
		perror("Couldn't bind the socket");
		exit(-1);
	}

	for (;;)
	{	
		if (listen(sfd, 1) < 0)
		{
			perror("Couldn't listen to the socket");
			exit(-1);
		}
		struct sockaddr_in clientaddr;
		int clientlen = sizeof(clientaddr) ;
		int* connfdp = (int*) malloc(sizeof(int));
		*connfdp = accept(sfd, (struct sockaddr*) &clientaddr, (socklen_t*) &clientlen);

		//TODO: fork child process which executes run_shell
		
	}

	return 0;
}

//TODO: get input from client via read(), execute input (shell functionality), return output to client via write()
void* run_shell(void* data)
{
	char buf[256];
	int connfdp = (*((int *)data));
	
	//does not work yet: received texts are empty
	if(read(connfdp, buf, sizeof(buf)) < 0)
	{
		perror("nothing received\n");
		exit(-1);
	}
	printf("received %s\n",buf);
}