#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <fcntl.h>
#define SERVER_PORT 6000
int main()
{
	int client_socket;
	char buffer [256];
	struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(SERVER_PORT);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	client_socket = socket ( AF_INET , SOCK_STREAM , IPPROTO_TCP );
	if (connect ( client_socket , (struct sockaddr * ) &server , sizeof(server))==0)
		printf("Client is connected to the server!\n");
	else
		printf("Error in connecting to the server\n");
	char filename[50];
	sprintf(filename,"%s", "from.txt");
	write(client_socket, filename, 50);
	printf("File name is sent to server successfully!\n");
	FILE *fp;
	fp = fopen("client_cpy.txt", "a");
	while(1) 
	{
		bzero(buffer,256);
                read(client_socket , buffer , 256) ;
		if(strcmp(buffer, "$")==0)
                        break;
                fputs(buffer, fp);
	}
	printf("END of client!\n");
	fclose(fp);
return 0;
}
