//DOM-KLRR-MAIN - Projeto Dominó
//##-08-25 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include <stdio.h>

#include "DOM-KLRR-MODEL.cpp"
Peca peca[28];

#include "DOM-KLRR-CONTROLLER.cpp"

int main(){
	IniciarPecas();
	ApresentarPecas();
	Embaralhar();
	ApresentarPecas();	
	
	jogar();	
}
