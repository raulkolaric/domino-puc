//DOM-KLRR-VIEW - Projeto Dominó
//##-08-25 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DOM-KLRR-VIEW.h"

int op;

void menu() {
	printf("--------------Menu---------------\n");
	printf("1 - Iniciar jogo (2 jogadores)\n");
	printf("2 - Iniciar jogo (contra o computador)\n");
	printf("3 - Retornar ao jogo interrompido\n");
	printf("4 - Regras gerais do Jogo\n");
	printf("5 - Salvar o jogo\n");
	printf("6 - Recuperar o jogo salvo\n");
	printf("0 – Sair do programa\n");
	printf("Opcao selecionada: %d\n", &op);
}
