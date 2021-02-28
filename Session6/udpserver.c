#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main() {
	int server_socket;
	char buffer[256];
	char hello_msg[256];
	struct sockaddr_in server_address, client_address;
	if ( (server_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
	{
		printf("error: socket creation failed\n");
		return -1;
	}
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_address.sin_port = htons(6000);
	if ( bind(server_socket, (const struct sockaddr *)&server_address,sizeof(server_address)) < 0 )
	{
		printf("error: bind failed\n");
		return (-1);
	}
	while(1)
	{
		int client_address_len = sizeof(client_address);
		int n;
		n = recvfrom(server_socket, (char *)buffer, 255, MSG_WAITALL, ( struct sockaddr*) &client_address, &client_address_len);
		buffer[n] = '\0';
		char* token1 = strtok(buffer, " ");
		char* token2 = strtok(NULL, " ");
		int a = atoi(token1);
		int b = atoi(token2);
		int c = a + b;
		char res[50];
		sprintf(res, "%d", c);
		sendto(server_socket, (const char *)res, strlen(res),MSG_CONFIRM,(const struct sockaddr *) &client_address, client_address_len);
		printf("Result sent successfully!\n");
	}
	return 0;
}
