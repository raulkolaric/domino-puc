//DOM-KLRR-MODEL - Projeto Domin�
//##-08-25 - Grupo: KLRR
//Kau� Bezerra Brito
//Raul Kolaric
//Rodrigo Ward Leite

#include <time.h>	//Necess�rio pois cont�m a vari�vel NULL
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
