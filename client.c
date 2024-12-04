#include "common.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSZ 1024


void usage(int argc, char **argv)
{
	printf("usage: %s <server IP> <server port>\n", argv[0]);
	printf("example: %s 127.0.0.1 51511\n", argv[0]);
	exit(EXIT_FAILURE);
}

int startConnection(int argc, char **argv, int s)
{
	if(argc < 3){
		usage(argc, argv);
	}

	struct sockaddr_storage storage;
	if(0 != addrparse(argv[1], argv[2], &storage)){
		usage(argc, argv);
	}

	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if(s == -1){
		logexit("socket");
	}
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if(0 != connect(s, addr, sizeof(storage))){
		logexit("connect");
	}
	return s;
}

void lowerCase(char *word) {
    int length = strlen(word); // Calcula o comprimento da string
    // Loop para percorrer cada caractere da string
    for (int i = 0; i < length; i++) {
        // Se o caractere estiver em maiúsculas (A-Z), converte para minúsculas (a-z)
        if (word[i] < 97) {
            word[i] = word[i] + 32; // 'A' (65) -> 'a' (97) = +32
        }
    }
}

int checkCommand(int *action, int *direction){
	char command[6] =" ";
	zeroVector(action);
	zeroVector(direction);
	scanf("%s", command);
	lowerCase(command);
	if(!strcmp(command, "start")){	// Comparação correta é com "start"
		*action = 0; // Retorna 0
		return 0;
	}else if(!strcmp(command, "up")){   // Comparação correta é com "up"
        *action = 1;
        *direction = 1;
        return 1;  // Retorna 1 se a direção for "up"
    }else if (!strcmp(command, "right")){ // Correção aqui também
        *action = 1;
        *direction = 2;
        return 1;  // Retorna 2 se a direção for "right"
    } else if (!strcmp(command, "down")) { // Correção aqui também
        *action = 1;
        direction[0] = 3;
        return 1; // Retorna 3 se a direção for "down"
    } else if(!strcmp(command, "left")){ // Correção aqui também
        *action = 1;
        *direction = 4;
        return 1;  // Retorna 4 se a direção for "left"
    } else {
        printf("error: command not found\n"); // Mensagem de erro se o comando for inválido
        return 1;
    }
}

void ShowWays(int *moves){
    int i = 0;

    printf("Possible moves: ");
    while(1){
       if(moves[i] == 1){
        printf("up");
       }else if(moves[i] == 2){
        printf("right");
       }else if(moves[i] == 3){
        printf("down");
       }else if(moves[i] == 4){
        printf("left");
       }
       if(moves[i+1]!=0){
        printf(", ");
       }else{
        printf(".\n");
        break;
       }
       i++;
    }
}

int main(int argc, char **argv){
		int s; 													// Inicialização do Socket
		s = startConnection(argc, argv, s); 					// Faz socket(), bind(), listen() e accept()

		struct action Jogo; 									//Declara estrutura

		while(checkCommand(&Jogo.type,Jogo.moves)){ 			//Enquando o retorno do teclado não for type 0 repita
			printf("error: start the game first\n");
		}

		char buf[BUFSZ];
		unsigned total = 0;
		size_t count = 0;

		count = send(s, &Jogo.type, sizeof(int), 0); 			//Envia comando star ao servidor
		if(count != sizeof(int)){
			logexit("send");
		}	

		int movecpy[4];	

		zeroVector(movecpy);

		recv(s,&Jogo,sizeof(Jogo), 0);				//Recebe os movimentos possíveis do jogador

		printf("Type: %i\nMove: %i\n",Jogo.type,Jogo.moves[0]);






		ShowWays(movecpy);									//Mostra na tela as opções

		int n = 0;
		
		while(1){
			checkCommand(&Jogo.type,Jogo.moves);			//Lê comando no teclado
			if(Jogo.moves[0] == movecpy[0] || Jogo.moves[0] == movecpy[1] || Jogo.moves[2] == movecpy[3] ||Jogo.moves[0] == movecpy[4]){
				break;
			}else printf("error: you cannot go this way\n");
		}

		count = send(s, Jogo.moves, sizeof(Jogo.moves), 0);		//Envia o movimento escolhido
		if(count != sizeof(Jogo.moves)){  
			logexit("send");
		}
		
		






















		/*memset(buf, 0, BUFSZ);
		fgets(buf, BUFSZ - 1, stdin);
		count = send(s, buf, strlen(buf) + 1, 0);
		if (count != strlen(buf) + 1){
			logexit("send");
		}*/
		//memset(buf, 0, BUFSZ);
		close(s);

		exit(EXIT_SUCCESS);
	}