#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "header.h"

void gotoxy(int x, int y){
  printf("%c[%d;%df", 0x1B, y, x);
}

void limpa(){ 
    int ch;
    while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}

void titulo(char nome[]){
  gotoxy(35,2);
  printf(FUN_BLA GRE"Lava-carros do(a) %s."RESET, nome);
}

void intro(char nome[], int *n_carros){
  gotoxy(30,2);
  printf(FUN_BLA GRE"SISTEMA GERENCIADOR DE LAVA-CARROS\n"RESET);
  printf(FUN_BLA YEL"\nSeja bem-vindo!!! Este software simulará o funcionamento de um lava-carros e gerenciará sua fila de lavagem e de espera, além da alocação de automóveis no pátio.");
  printf("\n\n- Como é o seu nome? "RESET);
  fgets(nome, 30, stdin);
  nome[strcspn(nome, "\n")]=0;
  printf(FUN_BLA YEL"\n- Seja bem-vindo(a) "BLU"%s"YEL", clique"BLU" ENTER"YEL" para começar..."RESET, nome);
  getchar();
  system("clear");

  printf(FUN_BLA YEL"\n- Por favor, informe a quantidade de carros a serem alocados no pátio: "RESET);
  scanf("%d", n_carros);
  while((*n_carros <= 0)||(*n_carros > 25)){
    system("clear");
    if(*n_carros <= 0){
      printf(FUN_BLA RED"\n- O valor \'%d\' é inválido. Por favor, digite um número inteiro positivo: "RESET, *n_carros);
    } else if(*n_carros > 25){
      printf(FUN_BLA RED"\n- Assim a gente não aguenta, escolha um valor abaixo de 25, por favor: "RESET);
    }
    scanf("%d", n_carros);
  } 
  system("clear");
}

int menu(int n_carros, int patio, int rua){
  int opc;
  gotoxy(32,15);
  printf(FUN_BLA GRE"MENU  DE  OPÇÕES"RESET);
  gotoxy(25,17);
  printf(FUN_BLA YEL"1. "GRE"Adicionar carro na fila;      "RESET);
  gotoxy(25,18);
  printf(FUN_BLA YEL"2. "GRE"Lavar carro (lava o primeiro);"RESET);
  gotoxy(25,19);
  printf(FUN_BLA YEL"3. "GRE"Consultar fila de lavagem;    "RESET);
  gotoxy(25,20);
  printf(FUN_BLA YEL"4. "GRE"Consultar fila de espera;     "RESET);
  gotoxy(25,21);
  printf(FUN_BLA YEL"5. "GRE"Encerrar;                     "RESET);
  
  gotoxy(65,18);
  printf(FUN_BLA GRE"Capacidade do pátio:"BLU" %d"RESET,n_carros);
  gotoxy(65,19);
  if((patio<n_carros)&&(patio!=0)){
    printf(FUN_BLA GRE"Carros no pátio:"YEL"     %d"RESET,patio);
  } else if(patio == n_carros){
    printf(FUN_BLA GRE"Carros no pátio:"RED"     %d"RESET,patio);
  } else if(patio == 0){
    printf(FUN_BLA GRE"Carros no pátio:"BLU"     %d"RESET,patio);
  }
  gotoxy(65,20);
  if(rua==0){
    printf(FUN_BLA GRE"Carros na rua:"BLU"       %d"RESET,rua);
  } else if((rua > 0)&&(rua<3)){
    printf(FUN_BLA GRE"Carros na rua:"YEL"       %d"RESET,rua);
  } else if(rua==3){
    printf(FUN_BLA GRE"Carros na rua:"RED"       %d"RESET,rua);
  }
  gotoxy(25,23);
  printf(FUN_BLA YEL"Escolha uma opção: "RESET);
  scanf("%d", &opc);
  system("clear");
  return opc;
}

void add_carro(int n_carros, int *patio, int *rua, struct TCarro vet_patio[], struct TCarro vet_rua[], char nome[]){
  if(*patio < n_carros){
    criaCarro(&vet_patio[*patio], nome);
    *patio += 1;
    gotoxy(32,5);
    printf(FUN_BLA BLU"Carro estacionado no pátio...\n"RESET);
  } else if((*patio == n_carros) && (*rua < 3)){
    criaCarro(&vet_rua[*rua], nome);
    *rua += 1;
    gotoxy(30,5);
    printf(FUN_BLA YEL"Pátio cheio, carro estacionado na rua.\n"RESET);
  } else if((*patio == n_carros) && (*rua == 3)){
    gotoxy(27,5);
    printf(FUN_BLA RED"Estamos sem espaço, volte mais tarde!\n"RESET);
  }
}

void criaCarro(struct TCarro *carro, char nome[]){
  titulo(nome);
  limpa();
  gotoxy(1,4);
  printf(FUN_BLA BLU"\nProprietário do carro: "RESET);
  fgets(carro->dono, 50, stdin);
  printf(FUN_BLA BLU"Placa do carro: "RESET);
  fgets(carro->placa, 10, stdin);
  printf(FUN_BLA BLU"Modelo do carro: "RESET);
  fgets(carro->modelo, 20, stdin);
  printf(FUN_BLA BLU"Cor do carro: "RESET);
  fgets(carro->cor, 15, stdin);
  printf(FUN_BLA"\n- Clique enter para voltar ao menu."RESET);
  limpa();

  carro->dono[strcspn(carro->dono, "\n")]=0;
  carro->placa[strcspn(carro->placa, "\n")]=0;
  carro->modelo[strcspn(carro->modelo, "\n")]=0;
  carro->cor[strcspn(carro->cor, "\n")]=0;
  system("clear");
}

void rem_carro(int n_carros, int *patio, int *rua, struct TCarro vet_patio[], struct TCarro vet_rua[]){
  lavaCarro(vet_patio, vet_rua, patio, rua, n_carros);
  if((*patio == n_carros) && (*rua <= 3) && (*rua > 0)){
    *rua -= 1;
    gotoxy(39,5);
    printf(FUN_BLA BLU"Carro lavado.\n"RESET);
  } else if(*patio > 0){
    *patio -= 1;
    gotoxy(39,5);
    printf(FUN_BLA YEL"Carro lavado.\n"RESET);
  } else{
    gotoxy(39,5);
    printf(FUN_BLA RED"Pátio vazio!\n"RESET);
  }
}

void lavaCarro(struct TCarro vet_patio[], struct TCarro vet_rua[], int *patio, int *rua, int n_carros){
  for(int i=0;i<*patio;i++){
    strcpy(vet_patio[i].dono,vet_patio[i+1].dono);
    strcpy(vet_patio[i].placa,vet_patio[i+1].placa);
    strcpy(vet_patio[i].modelo,vet_patio[i+1].modelo);
    strcpy(vet_patio[i].cor,vet_patio[i+1].cor);
  }
  strcpy(vet_patio[n_carros-1].dono,vet_rua[0].dono);
  strcpy(vet_patio[n_carros-1].placa,vet_rua[0].placa);
  strcpy(vet_patio[n_carros-1].modelo,vet_rua[0].modelo);
  strcpy(vet_patio[n_carros-1].cor,vet_rua[0].cor);
  for(int i=0;i<*rua;i++){
    strcpy(vet_rua[i].dono,vet_rua[i+1].dono);
    strcpy(vet_rua[i].placa,vet_rua[i+1].placa);
    strcpy(vet_rua[i].modelo,vet_rua[i+1].modelo);
    strcpy(vet_rua[i].cor,vet_rua[i+1].cor);
  }
}

void lavagem(struct TCarro vet_patio[], int patio, char nome[]){
  system("clear");
  titulo(nome);
  gotoxy(38,5);
  printf(FUN_BLA LIG_GRE"Fila de lavagem!\n"RESET); 
  for(int i = 0;i<patio;i++){
    printf(FUN_BLA YEL"\n\n- CARRO %d\n"RESET, i+1);
    printf(FUN_BLA BLU"%s\n"RESET, vet_patio[i].dono);
    printf(FUN_BLA BLU"%s\n"RESET, vet_patio[i].placa);
    printf(FUN_BLA BLU"%s\n"RESET, vet_patio[i].modelo);
    printf(FUN_BLA BLU"%s\n"RESET, vet_patio[i].cor);
  }
  if(patio == 0){
    printf(FUN_BLA RED"\n\nFila vazia...\n"RESET);
  }
  limpa();
  printf(FUN_BLA"\n\n- Clique enter para voltar ao menu."RESET);
  getchar();
  system("clear");
}

void espera(struct TCarro vet_rua[], int rua, char nome[], int patio){
  system("clear");
  titulo(nome);
  gotoxy(39,5);
  printf(FUN_BLA LIG_GRE"Fila de espera!\n"RESET);
  for(int i = 0;i<rua;i++){
    printf(FUN_BLA YEL"\n\n- CARRO %d\n"RESET, patio+i+1);
    printf(FUN_BLA BLU"%s\n"RESET, vet_rua[i].dono);
    printf(FUN_BLA BLU"%s\n"RESET, vet_rua[i].placa);
    printf(FUN_BLA BLU"%s\n"RESET, vet_rua[i].modelo);
    printf(FUN_BLA BLU"%s\n"RESET, vet_rua[i].cor);
  }
  if(rua == 0){
    printf(FUN_BLA RED"\n\nFila vazia...\n"RESET);
  }
  limpa();
  printf(FUN_BLA"\n\n- Clique enter para voltar ao menu."RESET);
  getchar();
  system("clear");
}

void encerra_programa(){
  gotoxy(25,19);
  printf(FUN_BLA GRE"Obrigado pela confiança. Volte sempre!\n"RESET);
}