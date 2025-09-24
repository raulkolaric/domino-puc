//DOM-KLRR-MODEL.cpp - Projeto Dominó
//23/09/2025 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include "DOM-KLRR-MODEL.h"

//Criar todas as 28 peças possíveis do dominó
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
