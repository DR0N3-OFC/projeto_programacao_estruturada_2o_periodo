#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

int main(void) {
  int n_carros, opc, patio = 0, rua = 0;
  struct TCarro *vet_patio, vet_rua[3];
  char nome[30];

  system("clear");
  
  //Introdução do Programa
  intro(nome, &n_carros);
  vet_patio = (struct TCarro *) malloc(sizeof(struct TCarro)*n_carros);
  //Menu do Programa
  titulo(nome);
  
  do{
    titulo(nome);
    opc = menu(n_carros, patio, rua);

    switch(opc){
      case 1: //Adicionar carro
        add_carro(n_carros, &patio, &rua, vet_patio, vet_rua, nome);
        break;
      case 2: //Lavar carro (remover)
        rem_carro(n_carros, &patio, &rua, vet_patio, vet_rua);
        break;
      case 3: //Fila de lavagem
        lavagem(vet_patio, patio, nome);
        break;
      case 4: //Fila de espera
        espera(vet_rua, rua, nome, patio);
        break;
      case 5: //Encerrar
        encerra_programa();
        break;
      default: //Opção inválida
        gotoxy(37,5);
        printf(FUN_BLA RED"Opção inválida (;~;)\n"RESET);
        break;    
    }
  }while(opc != 5);

  return 0;
}