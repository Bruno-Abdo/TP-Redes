#include<stdio.h>
#include<string.h>
#include"rules.h"


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

void ShowWays(int moves[100]){
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

int checkCommand(char *command,int *action, int *direction){
    scanf("%s",command);
    lowerCase(command);
    if(!strcmp(command, "start")) {   // Comparação correta é com "up"
        *action = 0;  // Retorna 1 se a direção for "up"
        return 0;
    }else if (!strcmp(command, "map")) { // Correção aqui também
        *action = 2;  // Retorna 2 se a direção for "right"
        return 2;
    }else if (!strcmp(command, "hint")) { // Correção aqui também
        *action = 3;  // Retorna 2 se a direção for "right"
        return 3;
    }else if (!strcmp(command, "reset")) { // Correção aqui também
        *action = 6;  // Retorna 2 se a direção for "right" [ u]5
        return 6;
    }else if (!strcmp(command, "exit")) { // Correção aqui também
        *action = 7;  // Retorna 2 se a direção for "right"
        return 7;
    }else if (!strcmp(command, "up")) {   // Comparação correta é com "up"
        *action = 1;
        *direction = 1;
        return 1;  // Retorna 1 se a direção for "up"
    } else if (!strcmp(command, "right")) { // Correção aqui também
        *action = 1;
        *direction = 2;
        return 1;  // Retorna 2 se a direção for "right"
    } else if (!strcmp(command, "down")) { // Correção aqui também
        *action = 1;
        *direction = 3;
        return 1; // Retorna 3 se a direção for "down"
    } else if (!strcmp(command, "left")) { // Correção aqui também
        *action = 1;
        *direction = 4;
        return 1;  // Retorna 4 se a direção for "left"
    } else {
        printf("error: command not found\n"); // Mensagem de erro se o comando for inválido
        return 88;
    }
}

void showMap(int Col, int Row, int M[10][10]){
        for(int i =0; i<Col; i++){
            for(int j = 0; j<Row; j++){
                if(M[i][j] == 0){
                    printf("# ");
                }else if(M[i][j] == 1){
                    printf("_ ");
                }else if(M[i][j] == 2){
                    printf("> ");
                }else if(M[i][j] == 3){
                    printf("X ");
                }else if(M[i][j] == 4){
                    printf("? ");
                }else if(M[i][j] == 5){
                    printf("+ ");
                }
            }
            printf("\n");
        }
}