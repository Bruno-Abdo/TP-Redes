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
    printf("Client connected\n");

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
        else if (c != 9 && c != 10 && c != 13){
            M[i][j] = c-48;  // Armazena o caractere na matriz
            j++;      // Avança para a próxima coluna
        } 
        // Se o caractere for uma nova linha ('\n')
        else if (c == 10){
            *m = j;  // Atualiza o número de colunas da matriz
            i++;     // Avança para a próxima linha
            j = 0;   // Reseta o índice de colunas
        }
    }
    // Fecha o arquivo após a leitura
    fclose(arq);
}

void InOut(int *PosiAtual, int *Saida, int m, int n, int M[10][10]){
 for(int i = 0; i<m; i++){
        for(int j = 0; j<n; j++){
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

int nextMove(int *Movimentos,int *posic, int *saida, int *tipo){ 
        if(Movimentos[0] == 1){
            posic[1]--;
        }else if(Movimentos[0] == 2){
            posic[0]++;
        }else if(Movimentos[0] == 3){
            posic[1]++;
        }else if(Movimentos[0] == 4){
            posic[0]--;
        }

        if(posic[0] == saida[0] && posic[1] == saida[1]){
            *tipo = 5;
        }
}

void reMap(int Original[10][10],int Copy[10][10], int Col, int Lin, int Player[2]){
    for(int i = 0; i<10; i++){
        for(int j = 0; j<10;j++){
            if(i >= Lin || j >= Col){
                Copy[i][j] = -1;
            }else if(j == Player[0] && i == Player[1]){
                Copy[i][j] = 5;
                if(i>0){
                    Copy[i-1][j] = Original[i-1][j];
                }
                if(i < Lin-1){
                    Copy[i+1][j] = Original[i+1][j];
                }
                if(j> 0){
                    Copy[i][j-1] = Original[i][j-1];
                }
                if(j< Col-1){
                    Copy[i][j+1] = Original[i][j+1];
                }
                if(i> 0 && j>0){
                    Copy[i-1][j-1] = Original[i-1][j-1];
                }
                if(i < Lin-1 && j < Col -1){
                    Copy[i+1][j+1] = Original[i+1][j+1];
                }
                if(i < Lin-1 && j> 0){
                    Copy[i+1][j-1] = Original[i+1][j-1];
                }
                if(i>0 && j< Col-1){
                    Copy[i-1][j+1] = Original[i-1][j+1];
                }      
            }
        }
    }
}

int main(int argc, char **argv){

    struct action Jogo;
    int Colunas = 0;
    int Linhas = 0;
    int Jogador[2];//[0] Coluna - [1] Linha
    int Saida[2];//[0] Coluna - [1] Linha
    int Maze[10][10];
    int MapedMaze[10][10];
    int csock;
    char caddrstr[BUFSZ];
    size_t count = 0;
    int leave = 0;

    saveFile(&Colunas, &Linhas, Maze, argv);//Converte txt em matrix  

    csock = startConnection(argc, argv, caddrstr);//Conecta ao cliente
    count = recv(csock,&Jogo,sizeof(Jogo),0); //Recebe Mensagens
    if(count != sizeof(Jogo)){
        logexit("recv");
    }

    while(1){

    for(int i = 0; i<10; i++){
        for(int j = 0; j<10; j++){
            MapedMaze[i][j] = 4;
        }
    }

    if(Jogo.type == 0){
        leave = 1;
        InOut(Jogador,Saida, Colunas, Linhas,Maze);//Encontra posição do jogador e da saida
        PossibleWays(Jogador[0],Jogador[1], Jogo.moves,Maze,Colunas,Linhas); //Define os movimentos possíveis para o jogador
        reMap(Maze,MapedMaze,Colunas,Linhas,Jogador);
        Jogo.type = 4;
        count = send(csock,&Jogo,sizeof(Jogo),0);                        //Envia movimentos possiveis ao cliente
        if(count != sizeof(Jogo)){
            logexit("send");
        }
        printf("starting new game\n");
    }


    while(leave){
        count = recv(csock,&Jogo,sizeof(Jogo),0); //Recebe Mensagens
        if(count != sizeof(Jogo)){
            logexit("recv");
        }
        if(Jogo.type == 1){
            nextMove(Jogo.moves,Jogador,Saida,&Jogo.type);
            reMap(Maze,MapedMaze,Colunas,Linhas,Jogador);
            PossibleWays(Jogador[0],Jogador[1], Jogo.moves,Maze,Colunas,Linhas);
            if(Jogo.type == 1){
                Jogo.type = 4;
                count = send(csock, &Jogo,sizeof(Jogo),0);//Envia
                if(count != sizeof(Jogo)){
                    logexit("send");
                }
            }
        }

        if(Jogo.type == 2){
           for(int i = 0; i<10; i++){
                for(int j = 0; j<10; j++){
                    Jogo.board[i][j] = MapedMaze[i][j];
                }
            }
            Jogo.type = 4;
            count = send(csock, &Jogo,sizeof(Jogo),0);//Envia
            if(count != sizeof(Jogo)){
                logexit("send");
            }
        }

        if(Jogo.type == 5){ //Winning
            for(int i = 0; i<10; i++){
                for(int j = 0; j<10; j++){
                    Jogo.board[i][j] = Maze[i][j];
                }
            }

            count = send(csock, &Jogo,sizeof(Jogo),0);//Envia
            if(count != sizeof(Jogo)){
                logexit("send");
            }            
        }
        if(Jogo.type == 6){
            //printf("client disconnected\n");
            Jogo.type = 0;
            break;
        }
        if(Jogo.type == 7){
            printf("client disconnected\n");
            close(csock);
            exit(EXIT_SUCCESS);
            break;
        }

    }

    }
    

    exit(EXIT_SUCCESS);
}