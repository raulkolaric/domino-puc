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
	//ApresentarPecas();
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
	
	for (int i = 0; i < 27 ; i++) {
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
	
}
