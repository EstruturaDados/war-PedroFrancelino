#include <stdio.h>
#include <string.h>
 struct territorio{
    char nome[30],cor[10];
    int tropas;
  };
int main(){
 
struct territorio t[5];

  printf("Vamos cadastrar os 5 territorios iniciais do nosso mundo.\n");
  for(int i = 1; i <= 2; i++){
    printf("=======================================\n");
    
    printf("--- Cadastrando Territorio %d --- \n", i);
  
    printf("Nome do Territorio:\n");
    scanf("%29s", t[i].nome);
    printf("Cor do Exercito (ex: Azul, Verde...) \n");
    scanf("%9s", t[i].cor);
    printf("Numero de Tropas \n");
    scanf("%d", &t[i].tropas);
    printf("\n");
  }
  

   printf("Cadastro inicial concluido com sucesso!\n");
   printf("=======================================\n");
    printf("MAPA DO MUNDO - ESTADO ATUAL \n");
    printf("=======================================\n");
  for(int i = 1; i <= 5; i++){
    
    printf("TERRITORIO %d :\n",  i);
    printf(" - Nome: %s\n", t[i].nome);
    printf(" - Dominado por : Exercito  %s  \n", t[i].cor);
    printf(" - Tropas \n %d", t[i].tropas);
    printf("\n");
  }
  return 0;
}