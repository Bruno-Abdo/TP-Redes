#ifndef _RULES_H
#define _RULES_H

// Função que converte todos os caracteres de uma string para minúsculas
void lowerCase(char *word);

// Função que retorna um inteiro baseado na direção recebida como string
int movesTo(char *direction);

//Busca o labirinto em um arquivo txt e salva em uma matrix
void saveFile(int *m, int *n, int M[10][10]);

// Estrutura que define uma ação no labirinto (usada para sockets)
struct action {
    int type;               // Tipo de ação
    int moves[100];         // Vetor de movimentos possíveis
    int board[10][10];      // Matriz representando o labirinto
};


#endif