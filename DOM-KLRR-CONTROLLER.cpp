//DOM-KLRR-CONTROLLER - Projeto Domin�
//##-08-25 - Grupo: KLRR
//Kau� Bezerra Brito
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
	Embaralhar();
	ApresentarPecas();
	Sleep(1000);
	Embaralhar();
	ApresentarPecas();
	Sleep(1000);
	Embaralhar();
	ApresentarPecas();
	Sleep(1000);
//	menu();
}

//fun��es
void Embaralhar () {
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

void limpaTela() {
	system("cls");
}
