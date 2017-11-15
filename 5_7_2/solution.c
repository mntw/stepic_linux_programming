#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFSIZE 5000

struct sockaddr_in local;

int main (int argc, char ** argv) {
    
    if (argc != 2) return -1;
    int port = atoi(argv[1]);

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    //printf("socket = %d\n", s);
    
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    int result = bind(s, (struct sockaddr*) &local, sizeof(local));
    //printf("%d\n", result);
    
    while (1) {
        char buf[BUFSIZE] = {0};
        read(s, buf, BUFSIZE);
        if (!strcmp(buf,"OFF\n")) 
            break;
        printf("%s\n", buf);
    
    }
    

    return 0;
}
