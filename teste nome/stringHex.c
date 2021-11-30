#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE *fpR;
    FILE *fpN; //Leitura
    FILE *fpC;
    FILE *fprep; //Escrita
    int escolha= '\0';
    unsigned char linha[50];
    unsigned char linha2[50];
    int valor=0;
    int length;
    char hex[100];

    fpR= fopen("DatabaseImageUnformatted.txt", "r");
    if(fpR == NULL){
        printf("Erro ao abrir o arquivo DatabaseImageUnformatted.txt\n");
        return 0; // Sai do programa caso falhe ao abrir o arquivo
    }

    printf("Por favor escolha uma das opções\n");
    printf("Digite 1 para criar um arquivo de nomes novos\n");
    printf("Digite 2 para converter em HEX\n");
    scanf("%d", &escolha);

    if(escolha==1){
    fpC= fopen("NovosNomes.txt", "w");
        if(fpC == NULL){
            printf("Erro ao abrir o arquivo NovosNomes.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        while(!feof(fpR)){
            fscanf(fpR, "%[^\n]\n", linha); //Muda a posição do ponteiro para a próxima linha sem salvar seu conteúdo
            valor=0;
            int i;
            for(i=0; i<50; i++){
                valor= valor+ linha[i];
            }
            fprintf(fpC, "%d\n", valor);
        }
    }
    else if(escolha==2){
        fpN= fopen("string.txt", "r");
        if(fpN == NULL){
            printf("Erro ao abrir o arquivo string.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        fprep= fopen("hex.txt", "w");
        if(fprep == NULL){
            printf("Erro ao abrir o arquivo hex.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        while(!feof(fpN)){
            valor=0;
            fscanf(fpN, "%[^\n]\n", linha);
            length= strlen(linha);
            int i;
            int j;
            for(i= 0, j=0; i<length; i++, j+=2){
                sprintf(hex + j, "%02x", linha[i] & 0xff);
            }
            length= strlen(hex);
            for(i=0; i<length; i++)
                valor= valor+hex[i];
            printf("'%s' in hex is %s.\n", linha, hex);
            printf("Valor int de %s fica em: %d\n", hex, valor);
        }

    }
    else{
        printf("Escolha inválida\n");
        return 0;
    }
}

