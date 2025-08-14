//DOM-KLRR-MODEL - Projeto Dominó
//##-08-25 - Grupo: KLRR
//Kauã Bezerra Brito
//Raul Kolaric
//Rodrigo Ward Leite

#include <time.h>	//Necessário pois contém a variável NULL
#include "DOM-KLRR-MODEL.h"

//Gerar as pecas
void GerarPecas() {
	int p=0;
	
	for(int i=0;i<7;i++) {
		for(int j=i;j<7;j++) {
			pecas[p].ladoA=i;
			pecas[p].ladoB=j;
			pecas[p].status='B';
			p++;
		}
	}	
}
