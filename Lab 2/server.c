#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define PORT 27000
int main(){
	int sockfd, namelen;
	struct sockaddr_in serverAddr;
	int newSocket;
	struct sockaddr_in newAddr;
	char buffer[1024];
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	memset(&serverAddr, '\0', sizeof(serverAddr));
	printf("Socket has been created!\n");
	
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port=htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	
	bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	
	printf("Socket is bound to port %d!\n", PORT);
	namelen = sizeof(serverAddr);
	if (getsockname(sockfd, (struct sockaddr *) &serverAddr, &namelen) < 0)
   	{
 		exit(3);
   	}
	newSocket = sizeof(newAddr);

   	
	do{
		memset(buffer,0,1024);
		if(recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &newAddr, &newSocket) <0)
		{
			exit(4);
   		}
   		printf("Received message %s from domain %s port %d internet address %s\n", 
			buffer,
			(newAddr.sin_family == AF_INET?"AF_INET":"UNKNOWN"), 
			ntohs(newAddr.sin_port),
			inet_ntoa(newAddr.sin_addr));
		printf("Echoing back message: %s\n",buffer);
		if (sendto(sockfd, buffer, (strlen(buffer)+1), 0,
                 (struct sockaddr *)&newAddr, sizeof(newAddr)) < 0)
		{
			exit(2);
		}
		
	}
	while (strcmp(buffer, "TERMINATE") != 0);
	printf("Closing server!\n");
}
