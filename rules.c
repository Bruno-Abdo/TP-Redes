#include<stdio.h>
#include<string.h>
#include"rules.h"

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



