//DOM-KLRR-CONTROLLER - Projeto Dominó
//##-08-25 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <windows.h>

#include "DOM-KLRR-CONTROLLER.h"
#include "DOM-KLRR-VIEW.cpp"

void jogar() {
	prepararJogo();
	//Embaralhar();
	ApresentarPecas();
	//Sleep(1000);
	//menu();
}

//funções
void Embaralhar() {
	srand(time(0));
	int n=28;
	struct Peca temp;
	for(int i=n-1;i>0;i--) {
		int j = rand()%(n);
		temp=pecas[i];
		pecas[i]=pecas[j];
		pecas[j]=temp;
	}
}

void prepararJogo() {
	Embaralhar();
	Embaralhar();
	Embaralhar();
	
	for (int i = 0; i < 28 ; i++) {
		pecas[i].status = 0;
		mesa[i].ladoD = -1;
		mesa[i].ladoE = -1;
	}
	
	for (int i = 0; i < 7; i++) {
		pecas[i].status = '1';
	}
	
	for (int i = 7; i < 13 ; i++) {
		pecas[i].status = '2';
	}
}

void primeiroLance() {
	
	//primeiro jogador
	//Criação de variáveis
	int a = 0;
	int b = 0;
	int c = 0;
	int x = 0;
	//Varredura das peças do jogador !
	for (int i = 0; i < 7; i++) {
		if (pecas[i].ladoA == pecas[i].ladoB) {					//Seleciona a peça que tiver os lados iguais
			if ((pecas[i].ladoA + pecas[i].ladoB) > a) {		//A soma dos lados dessa peça vai ser atribuída à variável a
				a = pecas[i].ladoA + pecas[i].ladoB;			//Caso tenha outra peça com os lados iguais, as somas dos lados vão ser comparados
				x = i;
			}
			b = 1;	
		}
	}
	
	//Caso não tenha nenhuma peça com lados iguais, vai ter outra varredura 
	if (b == 0) {
		for (int i = 0; i < 7; i++) {
			if ((pecas[i].ladoA + pecas[i].ladoB) > c) {
				c = pecas[i].ladoA + pecas[i].ladoB;
				x = 1;
			}
		}
	}
	
	//segundo jogador
	int d = 0;
	int e = 0;
	int f = 0;
	int y = 0;
	for (int i = 7; i < 13; i++) {
		if (pecas[i].ladoA == pecas[i].ladoB) {
			if ((pecas[i].ladoA + pecas[i].ladoB) > d) {
				d = pecas[i].ladoA + pecas[i].ladoB;
				y = i;
			}
			e = 1;	
		}
	}
	
	if (e == 0) {
		for (int i = 7; i < 13; i++) {
			if ((pecas[i].ladoA + pecas[i].ladoB) > f) {
				f = pecas[i].ladoA + pecas[i].ladoB;
				y = i;
			}
		}
	}
	
	if (a > d) {
		jogadoratual = '1';
	}
	
	else if (d > a) {
		jogadoratual = '2';
	}
	
	else if (c > f) {
		jogadoratual = '1';
	}
	
	else if (f > c) {
		jogadoratual = '2';
	}
}

void trocarJogador() {
	
	if(jogadoratual == '1') {
		jogadoratual='2';
	}
	else {
		jogadoratual='1';
	}
		
}











