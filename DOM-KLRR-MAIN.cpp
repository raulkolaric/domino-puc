//DOM-KLRR-MAIN - Projeto Domin�
//##-08-25 - Grupo: KLRR
//Kau� Bezerra Brito
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
