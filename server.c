#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024

void usage(int argc, char **argv)
{
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

int startConnection(int argc, char **argv, char *straddr){
      if (argc < 3)
    {
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if (0 != server_sockaddr_init(argv[1], argv[2], &storage))
    {
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if (s == -1)
    {
        logexit("socket");
    }

    int enable = 1;
    if (0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)))
    {
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if (0 != bind(s, addr, sizeof(storage)))
    {
        logexit("bind");
    }

    if (0 != listen(s, 10))
    {
        logexit("listen");
    }

    
    addrtostr(addr, straddr, BUFSZ);
    puts(straddr);

    struct sockaddr_storage cstorage;
    struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
    socklen_t caddrlen = sizeof(cstorage);

    int sock = accept(s, caddr, &caddrlen);
    if (sock == -1)
    {
        logexit("accept");
    }


    
    return sock;
}


int main(int argc, char **argv)
{
    int csock;

    char caddrstr[BUFSZ]; 
    csock = startConnection(argc, argv, caddrstr);

    puts(caddrstr);
    
    printf("Client connected");

    char buf[BUFSZ];
    memset(buf, 0, BUFSZ);
    size_t count = recv(csock, buf, BUFSZ - 1, 0);
    printf("[msg] %s, %d bytes: %s\n", caddrstr, (int)count, buf);

    sprintf(buf, "remote endpoint: %.1000s\n", caddrstr);
    count = send(csock, buf, strlen(buf) + 1, 0);
    if (count != strlen(buf) + 1)
    {
        logexit("send");
    }

    close(csock);

    exit(EXIT_SUCCESS);
}