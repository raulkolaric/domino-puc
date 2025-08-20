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

char op1, op2;

void ApresentarPecas() {
	for (int l=0; l<28; l++) {
		printf("[%d|%d]	", pecas[l].ladoA, pecas[l].ladoB);
	}
	printf("\n\n");
}	

char menuInicial() {
	do {
		printf("--------------MENU---------------\n");
		printf("1 - Iniciar jogo (2 jogadores)\n");
		printf("2 - Iniciar jogo (contra o computador)\n");
		printf("3 - Retornar ao jogo interrompido\n");
		printf("4 - Regras gerais do Jogo\n");
		printf("5 - Salvar o jogo\n");
		printf("6 - Recuperar o jogo salvo\n");
		printf("0 - Sair do programa\n");
		printf("Opcao selecionada: ");
		scanf("%c", &op1);	
		
		if (op >= '0' && op <= '6')
			break;
			
		printf("Opcao invalida\n");		
	} while (1);
	return op; 
}

void submenu() {
	printf("J - Jogar (possíveis n1 ou n2)");
	printf("C - Comprar");
	printf("P – Passar");
	printf("S – Sair (interromper o jogo voltando ao menu inicial)");
	printf("Opcao selecionada: ");
	scanf("%d", &op2);
}

void apresentaMensagem(char mens[100]) {
	printf("%s\n", mens);	
}

void mesa() {
	
}

void apresentar_1jogador() {
	
}

void fclear() {
	char carac;
 	while( (carac = fgetc(stdin)) != EOF && carac != '\n') {}
}

void limpaTela() {
	system("cls");
}

