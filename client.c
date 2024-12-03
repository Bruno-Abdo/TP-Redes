#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

void usage(int argc, char **argv)
{
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

#define BUFSZ 1024

int startConnection(int argc, char **argv, int s){
	if (argc < 3)
	{
		usage(argc, argv);
	}

	struct sockaddr_storage storage;
	if (0 != addrparse(argv[1], argv[2], &storage))
	{
		usage(argc, argv);
	}

	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1)
	{
		logexit("socket");
	}
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(storage)))
	{
		logexit("connect");
	}
	
	return s;
}

int main(int argc, char **argv)
{
	int s;
	s = startConnection(argc, argv, s);

	char buf[BUFSZ];
	memset(buf, 0, BUFSZ);
	printf("mensagem> ");
	fgets(buf, BUFSZ - 1, stdin);
	size_t count = send(s, buf, strlen(buf) + 1, 0);
	if (count != strlen(buf) + 1)
	{
		logexit("send");
	}
	memset(buf, 0, BUFSZ);
	unsigned total = 0;
	while (1)
	{
		count = recv(s, buf + total, BUFSZ - total, 0);
		if (count == 0)
		{	// Connection terminated.
			break;
		}
		total += count;
	}
	printf("received %u bytes\n", total);
	puts(buf);

	close(s);

	//puts(buf);

	exit(EXIT_SUCCESS);
}