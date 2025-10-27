#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Struct de forma dinâmica
typedef struct{
    char *nome, *cor;
    int tropas;
}territorio;

// Vetores para missões e progresso
char *tasks[5] = {NULL};
int missoesCompleta[5] = {0}; // 0 = não concluída, 1 = concluída

void esperarEnter() {
    int c;
    while((c = getchar()) != '\n' && c != EOF); // limpa buffer
    printf("Pressione ENTER para continuar...\n");
    getchar();
}

// Função para sortear missão
void sorteioMissao(int resAtk, territorio p[]){
    int randomMission = (rand() % 4) + 1;
    int alvoMissao;

    switch(randomMission){
        case 1:
            tasks[resAtk-1] = strdup("Conquistar 1 territorio\n");
            break;
        case 2:
            do {
                alvoMissao = rand() % 5;
            } while (alvoMissao == (resAtk-1));
            tasks[resAtk-1] = malloc(100);
            sprintf(tasks[resAtk-1], "Eliminar todas as tropas do exercito %s\n", p[alvoMissao].cor);
            break;
        case 3:
            tasks[resAtk-1] = strdup("Conquistar 10 tropas\n");
            break;
        case 4:
            tasks[resAtk-1] = strdup("Dominar o exercito com maior numero de tropas\n");
            break;
    }

    printf("\n--- SUA MISSÃO (Exercito %s) ---\n", p[resAtk-1].cor);
    printf("%s", tasks[resAtk-1]);
    esperarEnter();
}

// Mostrar mapa
void mostrarMapa(territorio p[], int j){
    printf("========= MAPA DO MUNDO =========\n");
    for(int i=0; i<j; i++){
        printf("%d. %s (Exercito: %s, Tropas: %d)\n", i+1, p[i].nome, p[i].cor, p[i].tropas);
    }
    printf("=================================\n");
}

// Ataque e defesa
void atk_def(int resAtk,int resDef,territorio *p){
    int randomNumberAtk = rand() % 6 + 1;
    int randomNumberDef = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Ataque (%s): %d | Defesa (%s): %d\n", p[resAtk-1].nome, randomNumberAtk, p[resDef-1].nome, randomNumberDef);

    if(randomNumberAtk > randomNumberDef){
        p[resDef-1].tropas--;
        p[resAtk-1].tropas++;
        printf("VITÓRIA DO ATAQUE! O defensor perdeu 1 tropa.\n");
        if(p[resDef-1].tropas == 0){
            printf("CONQUISTA! %s foi dominado pelo Exercito %s\n", p[resDef-1].nome, p[resAtk-1].cor);
            missoesCompleta[resAtk-1] = 1; // marca missão como completa
        }
    } else {
        p[resAtk-1].tropas--;
        p[resDef-1].tropas++;
        printf("VITÓRIA DA DEFESA! O atacante perdeu 1 tropa.\n");
        if(p[resAtk-1].tropas == 0){
            printf("CONQUISTA! %s foi dominado pelo Exercito %s\n", p[resAtk-1].nome, p[resDef-1].cor);
            missoesCompleta[resDef-1] = 1;
        }
    }

    esperarEnter();
}

// Cadastro de territórios
void cadT(territorio p[], int n){
    char nome[30], cor[20];
    for(int i=0;i<n;i++){
        printf("\n--- Cadastrando Territorio %d ---\n", i+1);

        printf("Nome do Territorio: ");
        fflush(stdin);
        scanf("%s", nome);
        p[i].nome = malloc(strlen(nome)+1);
        strcpy(p[i].nome, nome);

        printf("Cor do Exercito: ");
        fflush(stdin);
        scanf("%s", cor);
        p[i].cor = malloc(strlen(cor)+1);
        strcpy(p[i].cor, cor);

        printf("Numero de Tropas: ");
        scanf("%d", &p[i].tropas);
    }
}

// Mostrar missões
void verMissao(territorio p[]){
    printf("\n--- MISSÕES ---\n");
    for(int i=0;i<5;i++){
        if(tasks[i]){
            printf("Exercito %s: %s", p[i].cor, tasks[i]);
            if(missoesCompleta[i])
                printf("Status: COMPLETA\n");
            else
                printf("Status: EM ANDAMENTO\n");
        }
    }
    esperarEnter();
}

// Liberar memória
void liberarMemoria(territorio *p, int n){
    for(int i=0;i<n;i++){
        free(p[i].nome);
        free(p[i].cor);
    }
    for(int i=0;i<5;i++){
        if(tasks[i]) free(tasks[i]);
    }
    free(p);
}

// Função principal de ações
void menuAcoes(territorio *p){
    int resOpcoes=0, resAtk=0, resDef=0;
    do{
        printf("\n--- MENU DE AÇÕES ---\n");
        printf("1 - Atacar\n");
        printf("2 - Ver Missão\n");
        printf("0 - Sair\n");
        printf("Escolha sua ação: ");
        scanf("%d", &resOpcoes);

        switch(resOpcoes){
            case 1:
                mostrarMapa(p,5);
                printf("Escolha o territorio atacante (1 a 5, 0 para voltar): ");
                scanf("%d", &resAtk);
                if(resAtk==0) break;
                sorteioMissao(resAtk, p);
                printf("Escolha o territorio defensor (1 a 5): ");
                scanf("%d", &resDef);
                if(resDef == resAtk){
                    printf("Erro! Escolha outro defensor.\n");
                    scanf("%d", &resDef);
                }
                atk_def(resAtk,resDef,p);
                break;
            case 2:
                verMissao(p);
                break;
            case 0:
                printf("Fim de jogo.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(resOpcoes!=0);
}

// Main
int main(){
    srand(time(NULL));

    territorio *p = malloc(5*sizeof(territorio));
    printf("Vamos cadastrar os 5 territórios iniciais do nosso mundo.\n");
    cadT(p,5);

    printf("\nCadastro inicial concluido com sucesso!\n");
    mostrarMapa(p,5);

    menuAcoes(p);

    liberarMemoria(p,5);
    return 0;
}