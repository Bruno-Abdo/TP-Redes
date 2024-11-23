#include<stdio.h>
#include<string.h>
#include"rules.h"

#define MAX_ROWS 10  // Número máximo de linhas do arquivo
#define MAX_COLS 10  // Número máximo de colunas por linha

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


void saveFile(int *m, int *n, int M[10][10]) {
    // Declaração das variáveis
    FILE *arq;  // Ponteiro para o arquivo que será lido
    char c;     // Variável para armazenar caracteres lidos do arquivo

    // Abre o arquivo no modo de leitura texto
    arq = fopen("C:/Users/Bruno Abdo/Documents/TPRdC/labirinto.txt", "rt");

    // Verifica se o arquivo foi aberto corretamente
    if (arq == NULL) {
        printf("Problemas na abertura do arquivo\n");
        return;  // Sai da função em caso de erro
    }
    // Inicializa os índices da matriz
    int i = 0;  // Índice para as linhas
    int j = 0;  // Índice para as colunas

    // Loop para leitura dos caracteres do arquivo
    while (1) {  
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
        // Exibe o caractere lido na tela
        printf("%c", c);
    }
    // Exibe o tamanho final da matriz
    printf("m %i e n %i\n", *m, *n);

    // Fecha o arquivo após a leitura
    fclose(arq);
}


