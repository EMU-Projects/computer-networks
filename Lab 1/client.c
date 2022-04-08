#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 27000
int main(){
	int clientSocket;
	struct sockaddr_in serverAddr;
	char buffer[1024];
	
	clientSocket = socket(PF_INET, SOCK_STREAM, 0);
	memset(&serverAddr, '\0', sizeof(serverAddr));
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port=htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	do{
		memset(buffer,0,1024);
		printf("Enter message to send: ");
		gets(buffer);
		send(clientSocket, buffer, strlen(buffer), 0);
		memset(buffer,0,1024);
		recv(clientSocket, buffer, 1024, 0);
		printf("\nMessage received: %s\n", buffer);
	}while (strcmp(buffer,"TERMINATE") != 0);
	
	printf("Closing client!\n");
}
