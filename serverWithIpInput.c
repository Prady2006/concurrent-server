#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(int argc , char **argv){
	int socket_desc ;
	char recv_msg[2000];
	char msg[] = "GET / HTTP/1.1\r\n\r\n";
	socket_desc = socket(AF_INET, SOCK_STREAM , 0 ) ;
	struct sockaddr_in server ;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	if(connect(socket_desc, (struct sockaddr *) &server , sizeof(server)) < 0 ){
		puts("connect error");
		return 1 ;
	}
	if(socket_desc == -1)
		printf("Couldn't create socket");
	printf("Connected \n");
	if( send(socket_desc, msg , strlen(msg) , 0) < 0){
		puts("Send failed");
		return -1;
	}
	puts("Data sent ");
	if(recv(socket_desc, recv_msg , 2000, 0 ) < 0){
		puts("Error in receiving data ");
		return -1 ;
	}
	puts(recv_msg);
	close(socket_desc);
	return 0 ;	
}
