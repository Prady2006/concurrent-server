#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>

int main(int argc , char **argv){
    // pass hostname with a.out to get its ip 
    char *hostname = argv[1];
    char ip[400];
    struct hostent *he ;
    struct in_addr **addr_list ;
    if( (he = gethostbyname(hostname)) == NULL){
        perror("gethostbyname");
        return -1 ;
    }
    addr_list = (struct in_addr **)he->h_addr_list;
    for(int i = 0 ; addr_list[i] != NULL ;i++){
        strcpy(ip , inet_ntoa(*addr_list[i])) ;
        printf("%s", ip);
    }
    return 0 ; 
}