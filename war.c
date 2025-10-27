#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



//struct de forma dinâmica
typedef struct{
    char *nome, *cor;
    int tropas;
}territorio;


void atk_def(int resAtk,int resDef,territorio *p){
int randomNumberAtk = rand()  % (6  + 1);
int randomNumberDef = rand()  % (6 + 1);

printf(" --- RESULTADO DA BATALHA --- \n");
printf("O atacante %s rolou um dado e tirou: %d\n", p[resAtk - 1].nome,randomNumberAtk);
printf("O defensor %s rolou um dado e tirou: %d\n",  p[resDef - 1].nome, randomNumberDef);
printf("\n");

if(randomNumberAtk > randomNumberDef){
        p[resDef  - 1].tropas--;
        p[resAtk - 1].tropas++;
        printf("VITORIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        printf("\n");
        
        if(p[resDef - 1].tropas == 0){
            printf("CONQUISTA! O territorio %s foi domindado pelo Exercito %s\n",p[resDef - 1].nome, p[resAtk - 1].cor);
            printf("\n");}
        }
            else{
        p[resAtk - 1].tropas--;
        p[resDef - 1].tropas++;
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        printf("\n");
        if(p[resAtk - 1].tropas == 0){
            printf("CONQUISTA! O territorio %s foi domindado pelo Exercito %s\n",p[resAtk - 1].nome, p[resDef - 1].cor);
            printf("\n");
        }
    }
        printf("=======================================\n");
        printf("  MAPA DO MUNDO - ESTADO ATUAL \n");
        printf("=======================================\n");
        for (int i = 0; i < 5; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, p[i].nome, p[i].cor, p[i].tropas);
    }
    return;
};

void liberarMemoria(territorio *p, int n) {
    for (int i = 0; i < n; i++) {
        free(p[i].nome);  // libera o nome do território
        free(p[i].cor);   // libera a cor do território
    }
    free(p); // libera o vetor principal
}

int main(){ 
    

    //definição d um vetor
    territorio *p = malloc(5 * sizeof(territorio));
    srand(time(NULL));

    char nome[30],cor[20];
    
    printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");

    // Cadastro dos territórios
    for (int i = 0; i < 5; i++) {
        printf("=======================================\n");
        printf("--- Cadastrando Territorio %d --- \n", i + 1);

        printf("Nome do Territorio:\n");
        fflush(stdin);
        scanf("%s", nome);
        p[i].nome = malloc(strlen(nome)  + 1);
        strcpy(p[i].nome, nome);
    


        printf("Cor do Exercito (ex: Azul, Verde...): \n");
        fflush(stdin);
        scanf("%s", cor);
        p[i].cor = malloc(strlen(cor)  + 1);
        strcpy(p[i].cor,cor);



        printf("Numero de Tropas: \n");
        scanf("%d", &p[i].tropas);
        
        
        
        printf("\n");
    }

    // Mostra mapa inicial
    printf("\nCadastro inicial concluido com sucesso!\n");
    printf("========== MAPA DO MUNDO =========\n");
    printf("  MAPA DO MUNDO - ESTADO ATUAL \n"); 
       for (int i = 0; i < 5; i++) {
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i + 1, p[i].nome, p[i].cor, p[i].tropas);
    }
    printf("=======================================\n");



    // Fase d ataque
    int resAtk, resDef;

    do{
    
    printf(" --- FASE DE ATAQUE --- \n");
    printf("Escolha o territorio atacante (1 a 5, ou 0 para sair)");
    scanf("%d", &resAtk);
    if(resAtk == 0){
         printf("Fim de jogo");
         break;
    }
    printf("Escolha o territorio defensor (1 a 5): \n");
        scanf("%d", &resDef);
    if(resDef == resAtk ){
        printf("Erro!Selecione novamente\n");
        printf("Escolha o territorio defensor (1 a 5): \n");
        scanf("%d", &resDef);
    }
   

    
    
    
    atk_def(resAtk, resDef, p);
   
}
    while(resAtk !=0);
  
    liberarMemoria(p, 5);
    return 0;
}