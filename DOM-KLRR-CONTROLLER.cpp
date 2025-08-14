//DOM-KLRR-CONTROLLER - Projeto Dominó
//##-08-25 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "DOM-KLRR-CONTROLLER.h"
#include "DOM-KLRR-VIEW.cpp"

void jogar() {
	menu();
	
}

//funções
void Embaralhar () {
	srand(time(0));
	int n=28;
	struct Peca temp;
	for(int i=n-1;i>0;i--) {
		int j = rand()%(n);
		temp=peca[i];
		peca[i]=peca[j];
		peca[j]=temp;
	}
}

void IniciarPecas() {
	int p=0;
	
	for(int i=0;i<7;i++) {
		for(int j=i;j<7;j++) {
			peca[p].ladoA=i;
			peca[p].ladoB=j;
			peca[p].status='B';
			p++;
		}
	}	
}

void ApresentarPecas() {
	for (int l=0; l<28; l++) {
		printf("[%d|%d]	", peca[l].ladoA, peca[l].ladoB);
	}
	printf("\n\n");
}	
