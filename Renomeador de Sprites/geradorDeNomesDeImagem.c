#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

int main(){
    FILE *fpR;
    FILE *fpN; //Leitura
    FILE *fpC; //Escrita
    FILE *fprep;
    int escolha= '\0';
    unsigned char linha[50];
    unsigned char linha2[50];
    wchar_t linhaW[50];
    long valor=0;
    int value;
    int length;
    char hex[50];
    int sucessos=0;
    int falhas=0;
    fpR= fopen("DatabaseImageUnformatted.txt", "r");
    if(fpR == NULL){
        printf("Erro ao abrir o arquivo DatabaseImageUnformatted.txt\n");
        return 0; // Sai do programa caso falhe ao abrir o arquivo
    }

    printf("Por favor escolha uma das opções\n");
    printf("Digite 1 para criar um arquivo de nomes novos\n");
    printf("Digite 2 para renomear os arquivos com os novos nomes\n");
    scanf("%d", &escolha);

    if(escolha==1){
    fpC= fopen("NovosNomes.txt", "w");
        if(fpC == NULL){
            printf("Erro ao abrir o arquivo NovosNomes.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        while(!feof(fpR)){
            //fscanf(fpR, "%[^\n]\n", linha); //Muda a posição do ponteiro para a próxima linha sem salvar seu conteúdo
            value=0;
            fscanf(fpR, "%[^\n]\n", linha);
            length= strlen(linha);
            int i;
            int j;
            for(i= 0, j=0; i<length; i++, j+=2){
                sprintf(hex + j, "%02x", linha[i] & 0xff);
            }
            length= strlen(hex);
            for(i=0; i<length; i++)
                value= value+hex[i];
            //fprintf(fpC, "%s.png\n", hex);
            fprintf(fpC, "%s\n", hex);
        }
    }
    else if(escolha==2){
        fpN= fopen("NovosNomes.txt", "r");
        if(fpN == NULL){
            printf("Erro ao abrir o arquivo NovosNomes.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        fprep= fopen("report.txt", "w");
        if(fprep == NULL){
            printf("Erro ao abrir o arquivo report.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        while(!feof(fpR)){
            fscanf(fpR, "%[^\n]\n", linha);
            fscanf(fpN, "%[^\n]\n", linha2);
            if(rename(linha, linha2)==0){
                printf("Renomeado com sucesso\n");
                sucessos++;
            }
            else{
                printf("Erro ao renomear\n");
                falhas++;
            }

        }
        fprintf(fprep, "%s", "Número de sucessos: ");
        fprintf(fprep, "%d\n", sucessos);
        fprintf(fprep, "%s", "Número de falhas: ");
        fprintf(fprep, "%d\n", falhas);
    }
    else{
        printf("Escolha inválida\n");
        return 0;
    }

    return 0;
}
