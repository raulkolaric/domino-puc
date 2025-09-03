//DOM-KLRR-MODEL.cpp - Projeto Dominó
//26/08/25 - Grupo: KLRR
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
			pecas[p].status = 'B';
			p++;
		}
	}	
}

if (fp = fopen("ARQTESTE", "w") == NULL) {
	printf("O arquivo ARQTESTE não pode ser aberto para gravação\n";)
	exit(0);
}

if (fp = fopen("ARQTESTE", "r") == NULL) {
	printf("O arquivo ARQTESTE não pode ser aberto para leitura\n";)
	exit(0);
}

pecas [28]

for(i = 0; i<28, i++) {
	if (fwrite(&pecas[i]), sizeof(struct Peca), 1, fp) != 1) {
		printf("Erro na eitura do arquivo ARQTESTE");
		break;
	}
}
