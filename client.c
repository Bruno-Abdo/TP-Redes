#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSZ 1024

void usage(int argc, char **argv) //IVerifica a conexão do servidor
{
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

int startConnection(int argc, char **argv, int s) //Implementa a conexão com o servidor socket() e connect()
{
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

void lowerCase(char *word) //Transforma letras maíusculas da entrada em minusculas
{
	int length = strlen(word); // Calcula o comprimento da string
	// Loop para percorrer cada caractere da string
	for (int i = 0; i < length; i++)
	{
		// Se o caractere estiver em maiúsculas (A-Z), converte para minúsculas (a-z)
		if (word[i] < 97)
		{
			word[i] = word[i] + 32; // 'A' (65) -> 'a' (97) = +32
		}
	}
}

int checkCommand(int *action, int *direction) // Verifica os comandos to teclado
{
	char command[6] = " ";
	scanf("%s", command);
	lowerCase(command);
	if (!strcmp(command, "start"))
	{				 // Se entrada for start
		*action = 0; // Retorna 0
		return 0;
	}
	else if (!strcmp(command, "map"))
	{				 
		*action = 2; 
		return 2;
	}
	else if (!strcmp(command, "reset"))
	{				 
		*action = 6; 
		return 6;
	}
	else if (!strcmp(command, "exit"))
	{				
		*action = 7; 
		return 7;
	}
	else if (!strcmp(command, "up"))
	{ // Comparação correta é com "up"
		*action = 1;
		*direction = 1;
		return 1; // Retorna 1 se a direção for "up"
	}
	else if (!strcmp(command, "right"))
	{ 
		*action = 1;
		*direction = 2;
		return 1; // Retorna 2 se a direção for "right"
	}
	else if (!strcmp(command, "down"))
	{ 
		*action = 1;
		*direction = 3;
		return 1; // Retorna 3 se a direção for "down"
	}
	else if (!strcmp(command, "left"))
	{ 
		*action = 1;
		*direction = 4;
		return 1; // Retorna 4 se a direção for "left"
	}
	else
	{
		printf("error: command not found\n"); // Mensagem de erro se o comando for inválido
		return 1;
	}
}

void ShowWays(int *moves) //Coloca na tela as direções recebidas de action Move
{
	int i = 0;

	printf("Possible moves: ");
	while (1)
	{
		if (moves[i] == 1)
		{
			printf("up");
		}
		else if (moves[i] == 2)
		{
			printf("right");
		}
		else if (moves[i] == 3)
		{
			printf("down");
		}
		else if (moves[i] == 4)
		{
			printf("left");
		}
		if (moves[i + 1] != 0)
		{
			printf(", ");
		}
		else
		{
			printf(".\n");
			break;
		}
		i++;
	}
}

void showMap(int Map[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (Map[i][j] == -1)
			{
				break;
			}
			else if (Map[i][j] == 0)
			{
				printf("#\t");
			}
			else if (Map[i][j] == 1)
			{
				printf("_\t");
			}
			else if (Map[i][j] == 2)
			{
				printf(">\t");
			}
			else if (Map[i][j] == 3)
			{
				printf("X\t");
			}
			else if (Map[i][j] == 4)
			{
				printf("?\t");
			}
			else if (Map[i][j] == 5)
			{
				printf("+\t");
			}
		}
		printf("\n");
	}

	printf("\n");
}

int main(int argc, char **argv)
{
	int s;				// Inicialização do Socket
	struct action Jogo; // Declara estrutura
	char buf[BUFSZ];
	unsigned total = 0;
	size_t count = 0;
	int buffer = 0;
	int winning = 0;

	s = startConnection(argc, argv, s); // Faz socket(), bind(), listen() e accept()

	while (checkCommand(&Jogo.type, Jogo.moves))
	{ // Enquando o retorno do teclado não for type 0 repita
		printf("error: start the game first\n");
	}

	count = send(s, &Jogo, sizeof(Jogo), 0); // Envia comando star ao servidor
	if (count != sizeof(Jogo))
	{
		logexit("send");
	}

	while (1)
	{

		recv(s, &Jogo, sizeof(Jogo), 0); // Recebe os movimentos possíveis do jogador

		ShowWays(Jogo.moves); // Mostra na tela as opções

		while (1)
		{
			checkCommand(&Jogo.type, &buffer); // Lê comando no teclado
			if (Jogo.type == 7)
			{
				count = send(s, &Jogo, sizeof(Jogo), 0); // Envia o movimento escolhido
				if (count != sizeof(Jogo))
				{
					logexit("send");
				}
				exit(EXIT_SUCCESS);
			}
			if (Jogo.type == 6)
			{
				count = send(s, &Jogo, sizeof(Jogo), 0); // Envia o movimento escolhido
				if (count != sizeof(Jogo))
				{
					logexit("send");
				}
				winning = 0;
				break;
			}

			if (Jogo.type == 1 && winning == 0)
			{
				if (Jogo.moves[0] == buffer || Jogo.moves[1] == buffer || Jogo.moves[2] == buffer || Jogo.moves[3] == buffer)
				{

					for (int y = 0; y < 100; y++)
					{
						Jogo.moves[y] = 0;
					}

					Jogo.moves[0] = buffer;
					count = send(s, &Jogo, sizeof(Jogo), 0); // Envia o movimento escolhido
					if (count != sizeof(Jogo))
					{
						logexit("send");
					}
					recv(s, &Jogo, sizeof(Jogo), 0); // Recebe os movimentos possíveis do jogador
					if (Jogo.type != 5)
					{
						ShowWays(Jogo.moves); // Mostra na tela as opções
					}
				}
				else
					printf("error: you cannot go this way\n");
			}

			if (Jogo.type == 2 && winning == 0)
			{
				count = send(s, &Jogo, sizeof(Jogo), 0); // Envia o movimento escolhido
				if (count != sizeof(Jogo))
				{
					logexit("send");
				}

				recv(s, &Jogo, sizeof(Jogo), 0); // Recebe os movimentos possíveis do jogador
				showMap(Jogo.board);
			}
			if (Jogo.type == 5 && winning == 0)
			{
				winning = 1;
				Jogo.type = 0;
				printf("You escaped!\n");
				showMap(Jogo.board);
				printf("\n");
			}
		}
	}
}