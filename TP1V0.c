#include <winsock2.h>   // Biblioteca para o uso de sockets no Windows
#include <ws2tcpip.h>   // Biblioteca para funções adicionais de sockets
#include <stdio.h>      // Biblioteca para entrada e saída padrão
#include <stdlib.h>     // Biblioteca para funções utilitárias como malloc, free
#include <string.h>     // Biblioteca para manipulação de strings

// Função que converte todos os caracteres de uma string para minúsculas
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

// Função que retorna um inteiro baseado na direção recebida como string
int movesTo(char *direction) {
    // Converte a string recebida para minúsculas
    lowerCase(direction);

    // Compara a direção recebida com as direções possíveis
    if (strcmp(direction, "up") == 0) {   // Comparação correta é com "up"
        return 1;  // Retorna 1 se a direção for "up"
    } else if (strcmp(direction, "right") == 0) { // Correção aqui também
        return 2;  // Retorna 2 se a direção for "right"
    } else if (strcmp(direction, "down") == 0) { // Correção aqui também
        return 3;  // Retorna 3 se a direção for "down"
    } else if (strcmp(direction, "left") == 0) { // Correção aqui também
        return 4;  // Retorna 4 se a direção for "left"
    } else {
        printf("Comando inválido\n"); // Mensagem de erro se o comando for inválido
        return 0; // Retorna 0 para comando inválido
    }
}

// Estrutura que define uma ação no labirinto (usada para sockets)
struct action {
    int type;               // Tipo de ação
    int moves[100];         // Vetor de movimentos possíveis
    int board[10][10];      // Matriz representando o labirinto
};

int main() {
    // Declara a string de entrada com tamanho máximo de 10 caracteres
    char Move[10] = "UP"; // Inicializa a string com "UP" para Debug

    // Usa `gets()` para receber uma nova string de entrada do usuário (Perigoso, mas funcional para testes)
    gets(Move);

    // Variável para armazenar o próximo movimento
    int Next = 0;

    // Loop até que um comando válido seja inserido (Next seja diferente de 0)
    while (!Next) {
        Next = movesTo(Move); // Chama a função movesTo e armazena o retorno
        printf("%i\n", Next); // Exibe o código correspondente à direção inserida
    }

    return 0; // Finaliza o programa
}
