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
    
    saveFile(&Colunas, &Linhas, Jogo.board);

    // Declara a string de entrada com tamanho máximo de 10 caracteres
    //char Move[10] = "UP"; // Inicializa a string com "UP" para Debug

    // Usa `gets()` para receber uma nova string de entrada do usuário (Perigoso, mas funcional para testes)
    //gets(Move);

    // Variável para armazenar o próximo movimento
    //int Next = 0;

    // Loop até que um comando válido seja inserido (Next seja diferente de 0)
   /* while (!Next) {
        Next = movesTo(Move); // Chama a função movesTo e armazena o retorno
        printf("%i\n", Next); // Exibe o código correspondente à direção inserida
    }*/

    





    return 0; // Finaliza o programa
}
