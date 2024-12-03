#include<stdio.h>
#include<string.h>
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

void nextMove(char *Move, int *Movimentos,int *posic){
    int Next = 0;
    while(1){
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
