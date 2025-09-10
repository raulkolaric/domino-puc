//DOM-KLRR-MODEL.cpp - Projeto Domin�
//09/09/2025 - Grupo: KLRR
//Kau� Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include "DOM-KLRR-MODEL.h"

//Criar todas as 28 pe�as poss�veis do domin�
void gerarPecas() {
	int p = 0;
	
	for(int i = 0; i < 7 ; i++) {
		for(int j = i; j < 7; j++) {
			pecas[p].ladoA = i;
			pecas[p].ladoB = j;
			pecas[p].status = 0;
			p++;
		}
	}	
}
