#include<winsock2.h>
#include<ws2tcpip.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>





void lowerCase(char *word){
    int lentgh = strlen(word);
    for(int i = 0; i<lentgh; i++){
        if(word[i]<97){
            word[i] = word[i]+32;
        }
    }
}

int movesTo(char *direction){

    lowerCase(direction);
    if(strcmp(direction,"up")!=0){
        return 1;
    }else if(strcmp(direction,"right")!=0){
        return 2;
    }else if(strcmp(direction,"down")!=0){
        return 3;
    }else if(strcmp(direction,"left")!=0){
        return 4;
    }else{
        printf("Comando inválido");
        return 0;
    }

    printf("%s\n",direction);
}


struct action
{
    int type;
    int moves[100];
    int board[10][10];
};



int main(){


    char Move[10] = {'U','P'}; //Declara a string de entrada - Entradda para Debug
    gets(Move);
    int Next = 0;
    while(!Next){
    Next = movesTo(Move);
    printf("%i\n",Next);
    }

    return 0;

}