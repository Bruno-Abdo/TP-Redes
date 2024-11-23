#include <winsock2.h>   // Biblioteca para o uso de sockets no Windows
#include <ws2tcpip.h>   // Biblioteca para funções adicionais de sockets
#include <stdio.h>      // Biblioteca para entrada e saída padrão
#include <stdlib.h>     // Biblioteca para funções utilitárias como malloc, free
#include <string.h>     // Biblioteca para manipulação de strings
#include"rules.h"


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
        //printf("%c", c);
    }
    // Exibe o tamanho final da matriz
    //printf("m %i e n %i\n", *m, *n);

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
        printf(".");
        break;
       }
       i++;
    }
}

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
        printf("Comando invalido\n"); // Mensagem de erro se o comando for inválido
        return 0; // Retorna 0 para comando inválido
    }
}

void nextMove(char *Move, int *Movimentos,int *posic){

    int Next = 0;
    while(1){
        while(!Next){
            ShowWays(Movimentos);
            scanf("\n%s",Move);
            Next = movesTo(Move);
        }
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

int checkCommand(char *command){
    scanf("%s",command);
    lowerCase(command);
    if (!strcmp(command, "start")) {   // Comparação correta é com "up"
        return 0;  // Retorna 1 se a direção for "up"
    } else if (!strcmp(command, "move")) { // Correção aqui também
        return 3;  // Retorna 2 se a direção for "right"

    }
}

int main() {

    struct action Jogo;
    int Colunas = 0;
    int Linhas = 0;
    int posicaoJogador[2];
    int saida[2];
    char Move[6] = "Up"; // Inicializa a string com "UP" para Debug
    


while(1){
    if (!checkCommand(Move)){
        saveFile(&Colunas, &Linhas, Jogo.board);
        InOut(posicaoJogador, saida, Colunas, Linhas, Jogo.board);
        while(1){
            PossibleWays(posicaoJogador[0],posicaoJogador[1], Jogo.moves, Jogo.board,Colunas,Linhas);
            nextMove(Move, Jogo.moves, posicaoJogador); // Chama a função movesTo e armazena o retorno
            if(posicaoJogador[0] == saida[0] && posicaoJogador[1] == saida[1]){
                printf("Voce ganhou o jogo!!!");
                break;
            }
        }
    }
    else printf("error: start the game first");
}


    return 0; // Finaliza o programa
}

/*

1. Lê o arquivo txt e salva em uma matrix - SaveFile
2. Encontra posição inicial e final - InOut
3. Descobre as Movimentações possíveis - PossibleWays
4. Mostra na tela as opções - ShowWays
5. Le a resposta e salva



*/