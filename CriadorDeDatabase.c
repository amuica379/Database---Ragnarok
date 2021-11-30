#include <stdio.h>
#include <stdlib.h>

int buscaSequencial(char *linha, char chave){
    int i;
    for(i=0; i<1000; i++){
        if(linha[i]==chave)
            return i;
        else
            return -1;
    }
}

int buscaPalavra(unsigned char *linha, unsigned char *palavra, int end){
    int i;
    for(i=0; i<(end-1); i++){
        if(linha[i]!=palavra[i])
            return -1;
    }
        return i;
}

void novoItem(unsigned char *linha, int index, FILE *fpW, int pularLinha){
    index++;
    if(pularLinha)
        fprintf(fpW, "\n");//Nova linha para novo item
    fprintf(fpW, "%c", '"');
    while(linha[index]!=']'){
        fprintf(fpW, "%c", linha[index]);
        index++;
    }
   // if(pularLinha)
       // fprintf(fpW, "%c", '"');
    fprintf(fpW, "%c", ',');
}

void novaPalavra(unsigned char *linha, int index, FILE *fpW, int ehSlot, int pularLinha){
    if(ehSlot){
        if(pularLinha){
            fprintf(fpW, "\n");//Nova linha para novo item
        fprintf(fpW, "%c", '"');
        }
        index+=3;
        fprintf(fpW, "%c", '[');
        while(linha[index]!=','){
            fprintf(fpW, "%c", linha[index]);
            index++;
        }
        fprintf(fpW, "%c", ']');
        fprintf(fpW, "%c", '"');
    }
    else{
        if(pularLinha){
            fprintf(fpW, "\n");//Nova linha para novo item
            fprintf(fpW, "%c", '"');
        }
        index+=4;
        while(linha[index]!='"'){
            fprintf(fpW, "%c", linha[index]);
            index++;
        }
        if(pularLinha)
            fprintf(fpW, "%c", '"');
    }
    fprintf(fpW, "%c", ',');
}

int main(){

    int escolha=0;

    printf("Escolha uma das opções para gerar uma database\n");
    printf("Digite 1 para criar uma database completa\n");
    printf("Digite 2 para criar uma database somente de IDs\n");
    printf("Digite 3 para criar uma database somente de Nomes\n");
    printf("Digite 4 para criar uma database somente de Nomes de Imagem\n");
    printf("Digite 5 para criar uma database somente de Slots\n");
    printf("Digite 6 para criar uma database somente de Imagens sem formatação\n");
    printf("Digite 7 para criar uma database completa com nomes em HEX\n");

    scanf("%d", &escolha);

    // Vetores para obter linha do arquivo
    unsigned char linha[1000];

    //Strings de referência
    unsigned char nomeFlag[22]= {"identifiedDisplayName"};
    unsigned char slotFlag[10]= {"slotCount"};
    unsigned char spriteFlag[23]= {"identifiedResourceName"};

    // Ponteiros para manipular o arquivo itemInfo.txt

    FILE *fpR; //Leitura
    FILE *fpW; //Escrita
    FILE *fpRR;

    // Abrindo o arquivo itemInfo.txt (fpR aponta para o primeiro caractere)

    fpR= fopen("itemInfoFormatado.txt", "r");
    if(fpR == NULL){
        printf("Erro ao abrir o arquivo itemInfoFormatado.txt\n");
        return 0; // Sai do programa caso falhe ao abrir o arquivo
    }

    if(escolha==1){//DATABASE COMPLETA
       // Abrindo o arquivo DatabaseBarril.txt

    fpW= fopen("DatabaseBarril.txt", "w");
    if(fpW == NULL){
        printf("Erro ao abrir o arquivo DatabaseBarril.txt\n");
        return 0; // Sai do programa caso falhe ao abrir o arquivo
    }

    //fprintf(fpW, "Organização: itemID,itemNome,itemSprite,itemSlots");
    //fprintf(fpW, "\n");

        //fscanf(fpR, "%*[^\n]\n"); //Muda a posição do ponteiro para a próxima linha sem salvar seu conteúdo
        //fscanf(fpR, "%[^\n]\n", linha); //Lê uma linha inteira e passa o ponteiro para a próxima linha.
        //fprintf(fpW, "%s", linha); //Escreve a linha no local onde o ponteiro aponta atualmente
        //fprintf(fpW, "\n"); //Muda a posição do ponteiro para a próxima linha

    int indexID;
    int indexNome;
    int indexSlots;
    int indexSprite;
    while(!feof(fpR)){ //Continua até atingir o final do arquivo (EOF)
        indexID=0;
        indexNome=0;
        indexSlots=0;
        indexSprite=0;
        fscanf(fpR, "%[^\n]\n", linha);
        indexNome= buscaPalavra(linha, nomeFlag, sizeof(nomeFlag));
        if(indexNome != -1) //Localizou um Nome de item
            novaPalavra(linha, indexNome, fpW, 0, 0);
        indexSlots= buscaPalavra(linha, slotFlag, sizeof(slotFlag));
        if(indexSlots != -1) //Localizou o número de slots do item
            novaPalavra(linha, indexSlots, fpW, 1, 0);
        indexID= buscaSequencial(linha, '[');
        if(indexID != -1) //Localizou um ID de item
            novoItem(linha, indexID, fpW, 1);
        indexSprite= buscaPalavra(linha, spriteFlag, sizeof(spriteFlag));
        if(indexSprite != -1) //Localizou um Nome de Sprite
            novaPalavra(linha, indexSprite, fpW, 0, 0);
    }

    fclose(fpR); //Fecha o arquivo atual
    fclose(fpW); //Fecha e salva o arquivo atual

    return 0;
    }
    else if(escolha==2){//DATABASE DE IDS
        fpW= fopen("DatabaseID.txt", "w");
        if(fpW == NULL){
            printf("Erro ao abrir o arquivo DatabaseID.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        int indexID;
            while(!feof(fpR)){ //Continua até atingir o final do arquivo (EOF)
        indexID=0;
        fscanf(fpR, "%[^\n]\n", linha);
        indexID= buscaSequencial(linha, '[');
        if(indexID != -1) //Localizou um ID de item
            novoItem(linha, indexID, fpW, 1);
            }
        }
    else if(escolha==3){//DATABASE DE NOMES
        fpW= fopen("DatabaseNome.txt", "w");
        if(fpW == NULL){
            printf("Erro ao abrir o arquivo DatabaseNome.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        int indexNome;
            while(!feof(fpR)){ //Continua até atingir o final do arquivo (EOF)
        indexNome=0;
        fscanf(fpR, "%[^\n]\n", linha);
        indexNome= buscaPalavra(linha, nomeFlag, sizeof(nomeFlag));
        if(indexNome != -1) //Localizou um ID de item
            novaPalavra(linha, indexNome, fpW, 0, 1);
            }
        }
    else if(escolha==4){//DATABASE DE NOMES DE IMAGEM
        fpW= fopen("DatabaseImage.txt", "w");
        if(fpW == NULL){
            printf("Erro ao abrir o arquivo DatabaseImage.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        int indexSprite;
            while(!feof(fpR)){ //Continua até atingir o final do arquivo (EOF)
        indexSprite=0;
        fscanf(fpR, "%[^\n]\n", linha);
        indexSprite= buscaPalavra(linha, spriteFlag, sizeof(spriteFlag));
        if(indexSprite != -1) //Localizou um ID de item
            novaPalavra(linha, indexSprite, fpW, 0, 1);
            }
        }
    else if(escolha==5){
        fpW= fopen("DatabaseSlot.txt", "w");
        if(fpW == NULL){
            printf("Erro ao abrir o arquivo DatabaseSlot.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        int indexSlots;
            while(!feof(fpR)){ //Continua até atingir o final do arquivo (EOF)
        indexSlots=0;
        fscanf(fpR, "%[^\n]\n", linha);
        indexSlots= buscaPalavra(linha, slotFlag, sizeof(slotFlag));
        if(indexSlots != -1) //Localizou um ID de item
            novaPalavra(linha, indexSlots, fpW, 1, 1);
            }
        }
    else if(escolha==6){//DATABASE DE NOMES DE IMAGEM SEM FORMATAÇÃO
        fpW= fopen("DatabaseImageUnformatted.txt", "w");
        if(fpW == NULL){
            printf("Erro ao abrir o arquivo DatabaseImageUnformatted.txt\n");
            return 0; // Sai do programa caso falhe ao abrir o arquivo
        }
        int indexSprite;
        while(!feof(fpR)){ //Continua até atingir o final do arquivo (EOF)
            indexSprite=0;
            fscanf(fpR, "%[^\n]\n", linha);
            indexSprite= buscaPalavra(linha, spriteFlag, sizeof(spriteFlag));
            if(indexSprite != -1){ //Localizou um ID de item
                fprintf(fpW, "\n");//Nova linha para novo item
                indexSprite+=4;
                while(linha[indexSprite]!='"'){
                    fprintf(fpW, "%c", linha[indexSprite]);
                    indexSprite++;
                }
                fprintf(fpW, "%s", ".png");
            }

        }
    }
    if(escolha==7){//DATABASE COMPLETA COM NOMES EM HEX

       // Abrindo o arquivo DatabaseBarril.txt

    fpW= fopen("DatabaseBarril.txt", "w");
    if(fpW == NULL){
        printf("Erro ao abrir o arquivo DatabaseBarril.txt\n");
        return 0; // Sai do programa caso falhe ao abrir o arquivo
    }

    fpRR= fopen("NovosNomes.txt", "r");
    if(fpRR == NULL){
        printf("Erro ao abrir o arquivo NovosNomes.txt\n");
        return 0; // Sai do programa caso falhe ao abrir o arquivo
    }

    //fprintf(fpW, "Organização: itemID,itemNome,itemSprite,itemSlots");
    //fprintf(fpW, "\n");

        //fscanf(fpR, "%*[^\n]\n"); //Muda a posição do ponteiro para a próxima linha sem salvar seu conteúdo
        //fscanf(fpR, "%[^\n]\n", linha); //Lê uma linha inteira e passa o ponteiro para a próxima linha.
        //fprintf(fpW, "%s", linha); //Escreve a linha no local onde o ponteiro aponta atualmente
        //fprintf(fpW, "\n"); //Muda a posição do ponteiro para a próxima linha

    int indexID;
    int indexNome;
    int indexSlots;
    int indexSprite;
    while(!feof(fpR)){ //Continua até atingir o final do arquivo (EOF)
        indexID=0;
        indexNome=0;
        indexSlots=0;
        indexSprite=0;
        fscanf(fpR, "%[^\n]\n", linha);
        indexNome= buscaPalavra(linha, nomeFlag, sizeof(nomeFlag));
        if(indexNome != -1) //Localizou um Nome de item
            novaPalavra(linha, indexNome, fpW, 0, 0);
        indexSlots= buscaPalavra(linha, slotFlag, sizeof(slotFlag));
        if(indexSlots != -1) //Localizou o número de slots do item
            novaPalavra(linha, indexSlots, fpW, 1, 0);
        indexID= buscaSequencial(linha, '[');
        if(indexID != -1) //Localizou um ID de item
            novoItem(linha, indexID, fpW, 1);
        indexSprite= buscaPalavra(linha, spriteFlag, sizeof(spriteFlag));
        if(indexSprite != -1){//Localizou um Nome de Sprite
            fscanf(fpRR, "%[^\n]\n", linha);
            fprintf(fpW, "%s", linha);
            fprintf(fpW, "%c", ',');
        }
    }

    fclose(fpR); //Fecha o arquivo atual
    fclose(fpW); //Fecha e salva o arquivo atual

    return 0;
    }
    else{
        printf("Escolha inválida\n");
        return 0;
    }
}



