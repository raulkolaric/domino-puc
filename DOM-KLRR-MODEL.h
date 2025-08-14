//DOM-KLRR-MODEL.h - Projeto Dominó
//##-08-25 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

void GerarPecas();

//Estrutura das peças
struct Peca {
	int ladoA;
	int ladoB;
	char status;	//NULL, '1', '2', 'M'
					//NULL = Disponível, 1= com jogador 1, 2 = com o jogador 2
} pecas[28];

//Variáveis globais
int mesaE, mesaD;	//Extremidades Esquerda e Direita da mesa

