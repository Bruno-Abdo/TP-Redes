#include <winsock2.h>   // Biblioteca para o uso de sockets no Windows
#include <ws2tcpip.h>   // Biblioteca para funções adicionais de sockets
#include <stdio.h>      // Biblioteca para entrada e saída padrão
#include <stdlib.h>     // Biblioteca para funções utilitárias como malloc, free
#include <string.h>     // Biblioteca para manipulação de strings
#include"rules.h"

int main() {

    struct action Jogo;
    int Colunas = 0;
    int Linhas = 0;
    int posicaoJogador[2];
    int saida[2];
    int way = 0;
    char Move[6];

    while(checkCommand(Move,&Jogo.type,&way)){
        printf("error: start the game first\n");
    }

    saveFile(&Colunas, &Linhas, Jogo.board);
    InOut(posicaoJogador, saida, Colunas, Linhas, Jogo.board);
    PossibleWays(posicaoJogador[0],posicaoJogador[1], Jogo.moves, Jogo.board,Colunas,Linhas);
    ShowWays(Jogo.moves);

    int playerPath[2][100];
    int aux = 0;
    for(int i =0; i<2; i++){
        for(int j = 0; j<100; j++){
            playerPath[i][j] = 0;
        }
    }


    if(checkCommand(Move,&Jogo.type,&way)==2){
        showMap(Colunas,Linhas,Jogo.board);
    }

   
    while(1){
        nextMove(Move, Jogo.moves, posicaoJogador); // Chama a função movesTo e armazena o retorno
        if(posicaoJogador[0] == saida[0] && posicaoJogador[1] == saida[1]){
            printf("Voce ganhou o jogo!!!");
            break;
        }
    }
    return 0; // Finaliza o programa
}