#include "common.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#define BUFSZ 1024

void usage(int argc, char **argv){
    printf("usage: %s <v4|v6> <server port>\n", argv[0]);
    printf("example: %s v4 51511\n", argv[0]);
    exit(EXIT_FAILURE);
}

int startConnection(int argc, char **argv, char *straddr)
{
    if(argc < 4){
        usage(argc, argv);
    }

    struct sockaddr_storage storage;
    if(0 != server_sockaddr_init(argv[1], argv[2], &storage)){
        usage(argc, argv);
    }

    int s;
    s = socket(storage.ss_family, SOCK_STREAM, 0);
    if(s == -1){
        logexit("socket");
    }

    int enable = 1;
    if(0 != setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int))){
        logexit("setsockopt");
    }

    struct sockaddr *addr = (struct sockaddr *)(&storage);
    if(0 != bind(s, addr, sizeof(storage))){
        logexit("bind");
    }

    if(0 != listen(s, 10)){
        logexit("listen");
    }

    struct sockaddr_storage cstorage;
    struct sockaddr *caddr = (struct sockaddr *)(&cstorage);
    socklen_t caddrlen = sizeof(cstorage);

    int sock = accept(s, caddr, &caddrlen);
    if (sock == -1)
    {
        logexit("accept");
    }

    char traddr[BUFSZ];
    addrtostr(caddr, straddr, BUFSZ);

    return sock;
}

void saveFile(int *m, int *n, int M[10][10], char **argv) {
    // Declaração das variáveis
    FILE *arq;  // Ponteiro para o arquivo que será lido
    char c;     // Variável para armazenar caracteres lidos do arquivo

    // Abre o arquivo no modo de leitura texto
    arq = fopen(argv[4], "rt");

    // Verifica se o arquivo foi aberto corretamente
    if (arq == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return;  // Sai da função em caso de erro
    }
    // Inicializa os índices da matriz
    int i = 0;  // Índice para as linhas
    int j = 0;  // Índice para as colunas

    // Loop para leitura dos caracteres do arquivo
    while (1){  
        // Lê um caractere do arquivo
        c = fgetc(arq);

        // Verifica se chegou ao final do arquivo (EOF)
        if (c == EOF) {
            *n = i;  // Atualiza o número de linhas
            break;   // Sai do loop
        } 
        // Se o caractere não for tabulação ('\t' = ASCII 9) ou nova linha ('\n' = ASCII 10)
        else if (c != 9 && c != 10) {
            M[i][j] = c-48;  // Armazena o caractere na matriz
            j++;          // Avança para a próxima coluna
        } 
        // Se o caractere for uma nova linha ('\n')
        else if (c == 10) {
            *m = j;  // Atualiza o número de colunas da matriz
            i++;     // Avança para a próxima linha
            j = 0;   // Reseta o índice de colunas
        }
    }
    // Fecha o arquivo após a leitura
    fclose(arq);
}

void InOut(int *PosiAtual, int *Saida, int m, int n, int M[10][10]){
 for(int i = 0; i<=m; i++){
        for(int j = 0; j<=n; j++){
            if(M[j][i] == 2){
                PosiAtual[0] = i;
                PosiAtual[1] = j;
            } else if(M[j][i] == 3){
                Saida[0] = i;
                Saida[1] = j;
            }
        }
    }
    //printf("Sua posicao e %i, %i. A saida esta em %i, %i",PosiAtual[0],PosiAtual[1],Saida[0],Saida[1]);
}

void PossibleWays(int PCol, int PRow, int Moves[100],int M[10][10], int col, int row){

    int k = 0;
    for(int i = 0; i<100;i++){
        Moves[i] = 0;
    }
    if(PRow> 0 && (M[PRow-1][PCol] != 0 )){
        Moves[k] = 1;
        k++;
    }
    if(PCol< col && (M[PRow][PCol+1] != 0 )){
        Moves[k] = 2;
        k++;
    }
    if(PRow< row && (M[PRow+1][PCol] != 0 )){
        Moves[k] = 3;
        k++;
    }
    if(PCol> 0 && (M[PRow][PCol-1] != 0)){
        Moves[k] = 4;
        k++;
    }
}

void nextMove(char *Move, int *Movimentos,int *posic){
    int Next = 0;
    while(1){
        if(Next == Movimentos[0] || Next == Movimentos[1] || Next == Movimentos[2] || Next == Movimentos[3]){
            if(Next == 1){
                posic[1]--;
            }else if(Next == 2){
                posic[0]++;
            }else if(Next == 3){
                posic[1]++;
            }else if(Next == 4){
                posic[0]--;
            }
            break;
        }else{
            printf("Movimento Invalido\n");
            Next = 0;
        }
    }
}

int main(int argc, char **argv){

    struct action Jogo;
    int Colunas = 0;
    int Linhas = 0;
    int Jogador[2];//[0] Coluna - [1] Linha
    int Saida[2];//[0] Coluna - [1] Linha

    saveFile(&Colunas, &Linhas, Jogo.board, argv);    

    int csock;
    char caddrstr[BUFSZ];

    csock = startConnection(argc, argv, caddrstr);
    printf("Client connected\n");
    
    size_t count = 0;
    count = recv(csock, &Jogo.type,sizeof(int), 0);

    if(Jogo.type == 0){
        InOut(Jogador,Saida, Colunas, Linhas,Jogo.board);
        PossibleWays(Jogador[0],Jogador[1], Jogo.moves, Jogo.board,Colunas,Linhas);
        count = send(csock,&Jogo.moves,sizeof(100)+1,0);
        printf("Chegou aqui");
        if (count != sizeof(100)+1){
				logexit("send");
			}
    }

    char buf[BUFSZ];
    while (1)    {
        memset(buf, 0, BUFSZ);
        count = recv(csock, buf, BUFSZ - 1, 0);
        puts(buf);

        memset(buf, 0, BUFSZ);
		printf("mensagem> ");
		fgets(buf, BUFSZ - 1, stdin);
		count = send(csock, buf, strlen(buf) + 1, 0);
		if (count != strlen(buf) + 1){
			logexit("send");
		}
    }

    close(csock);

    exit(EXIT_SUCCESS);
}