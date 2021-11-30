
#include <stdio.h>
#include <stdlib.h>

int main(){

    // Vetores para obter linha do arquivo
    char linha[1000];
    // Ponteiros para manipular o arquivo itemInfo.txt

    FILE *fpR; //Leitura
    FILE *fpW; //Escrita

    // Abrindo o arquivo itemInfo.txt (fpR aponta para o primeiro caractere)

    fpR= fopen("itemInfo.txt", "r");
    if(fpR == NULL){
        printf("Erro ao abrir o arquivo itemInfo.txt\n");
        return 0; // Sai do programa caso falhe ao abrir o arquivo
    }

    // Abrindo o arquivo DatabaseBarril.txt

    fpW= fopen("itemInfoFormatado.txt", "w");
    if(fpW == NULL){
        printf("Erro ao abrir o arquivo itemInfoFormatado.txt\n");
        return 0; // Sai do programa caso falhe ao abrir o arquivo
    }


        while(!feof(fpR)){
            fscanf(fpR, "%[^\n]\n", linha);
            fprintf(fpW, "%s\n", linha);
        }

    fclose(fpR); //Fecha o arquivo atual
    fclose(fpW); //Fecha e salva o arquivo atual

    return 0;
}
