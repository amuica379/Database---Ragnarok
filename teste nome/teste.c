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
    int contador=0;
    int iguais[6645];
    int valor=0;
    int stringsIguais=0;

    fpR= fopen("DatabaseImageUnformatted.txt", "r");
    if(fpR == NULL){
        printf("Erro ao abrir o arquivo DatabaseImageUnformatted.txt\n");
        return 0; // Sai do programa caso falhe ao abrir o arquivo
    }

    printf("Por favor escolha uma das opções\n");
    printf("Digite 1 para criar um arquivo de nomes novos\n");
    printf("Digite 2 para localizar Strings iguais\n");
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
        fpN= fopen("DatabaseImageUnformatted.txt", "r");
        if(fpN == NULL){
            printf("Erro ao abrir o arquivo DatabaseImageUnformatted.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        fprep= fopen("DatabaseImageUnformatted.txt", "r");
        if(fprep == NULL){
            printf("Erro ao abrir o arquivo DatabaseImageUnformatted.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        while(!feof(fpR)){
            fscanf(fpR, "%[^\n]\n", linha);
            while(!feof(fprep)){
                fscanf(fprep, "%[^\n]\n", linha2);
                if(strcmp(linha, linha2)==0){
                    iguais[contador]++;
                }
            }
            contador++;
            fseek(fprep, 0, SEEK_SET);
        }
        int i;
        for(i=0; i<6645; i++)
            stringsIguais= stringsIguais+iguais[i];
        printf("Strings iguais: %d\n", stringsIguais);

    }
    else{
        printf("Escolha inválida\n");
        return 0;
    }
}

