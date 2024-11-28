#ifndef _RULES_H
#define _RULES_H

// Função que converte todos os caracteres de uma string para minúsculas
void lowerCase(char *word);

// Função que retorna um inteiro baseado na direção recebida como string
int movesTo(char *direction);

//Busca o labirinto em um arquivo txt e salva em uma matrix
void saveFile(int *m, int *n, int M[10][10]);

void ShowWays(int moves[100]);

int checkCommand(char *command,int *action, int *direction);

void InOut(int *PosiAtual, int *Saida, int m, int n, int M[10][10]);

void PossibleWays(int PCol, int PRow, int Moves[100],int M[10][10], int col, int row);

void nextMove(char *Move, int *Movimentos,int *posic);

void showMap(int Col, int Row, int M[10][10]);

// Estrutura que define uma ação no labirinto (usada para sockets)
struct action {
    int type;               // Tipo de ação
    int moves[100];         // Vetor de movimentos possíveis
    int board[10][10];      // Matriz representando o labirinto
};


#endif