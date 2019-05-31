#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 9000
#define HOST "127.0.0.1"

int main()
{
	//getc(stdin);
	//printf("Client Exit\n");
	
	struct sockaddr_in addr = {
		.sin_family = AF_INET,
		.sin_port = htons(PORT),
		.sin_addr.s_addr = inet_addr(HOST)
	};

	int cfd;
	
	if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Couldn't open the socket");
		exit(-1);
	}

	//connect to the server
	if (connect(cfd, (struct sockaddr*) &addr, sizeof(addr)) < 0)
	{
		perror("Couldn't connect to socket");
		exit(-1);
	}

	while(1)
	{
		char* command = malloc(sizeof(char));
		int length=0;

		//read in user input from stdin
		char c = getc(stdin);
		while(c!='\n')
		{
			command=realloc(command,(length+2)*sizeof(char));
			command[length]=c;
			command[length+1]='\0';
			++length;
			c=getc(stdin);
		}
		printf("sending %s\n",command);

		//send user input to server
		if (write(cfd, command, (length)*sizeof(char) < 0))
		{
			perror("Couldn't send message");
			exit(-1);
		}
			
	}
	return 0;
}
