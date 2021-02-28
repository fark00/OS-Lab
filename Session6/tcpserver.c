#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define SERVER_PORT 6000
#define listenNumber 5
int main(){
	char buffer [256];
	int server_socket , client_socket ;
	struct sockaddr_in server_address , client_address ;
	server_address.sin_family=AF_INET; //IPv4
	server_address.sin_port=htons(SERVER_PORT);
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_socket = socket ( AF_INET , SOCK_STREAM , IPPROTO_TCP );
	bind ( server_socket , (struct sockaddr * ) & server_address , sizeof(server_address)) ;
	listen (server_socket , listenNumber);
	int clientsize=sizeof(client_address);
	if ((client_socket = accept ( server_socket , (struct sockaddr * ) &client_address , &(clientsize)))>=0)
		printf("A connection from a client is recieved\n");
	else
		printf("Error in accepting the connection from the client\n ");
	bzero(buffer, 256);
	read(client_socket, buffer, 256);
	FILE * fp = fopen(buffer, "r");
	printf("file is open!\n");
	char ch = fgetc(fp);
	char str[2];
	do
	{
		str[0]=ch;
       		str[1]='\0';
		sprintf(buffer,"%s", str);
                write(client_socket , buffer, 256);
		ch = fgetc(fp);
	} while(ch != EOF);
	sprintf(buffer,"%s", "$");
	write(client_socket, buffer, 256);
	printf("END od server!\n");
	return 0;
}
