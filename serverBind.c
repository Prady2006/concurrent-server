#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h> // inet_addr 
#include<netdb.h>
#include<unistd.h> // write 
#include<string.h>
#include<pthread.h>
int main(int argc , char **argv){
    int socket_desc , new_socket;
    int port = atoi(argv[1]);
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server , client  , server2;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    if( bind(socket_desc , (struct sockaddr *) &server , sizeof(server)) < 0 ){
        perror("bind failed");
        return -1;
    }
    puts("bind done ");
    listen(socket_desc, 5);
    puts("Listening on socket ...");
    int c = sizeof(struct sockaddr_in );
    while( (new_socket = accept(socket_desc, (struct sockaddr *) &client , (socklen_t *)&c ) ) ){
        if(new_socket < 0 ){
            perror("error in accepting connections ");
            return -1 ;
        }
        int a = sizeof c ;
        puts("Connection accepted ");
        char *msg = "hello client ttyl \n";
        printf(" %s connected from port %d ", inet_ntoa(client.sin_addr) , ntohs(client.sin_port));
        write(new_socket , msg , strlen(msg));
    }
    return 0 ;
}
