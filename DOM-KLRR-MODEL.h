//DOM-KLRR-MODEL.h - Projeto Domin�
//09/09/2025 - Grupo: KLRR
//Kau� Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include <time.h>	//Necess�rio pois cont�m a vari�vel NULL

//Gera todas as 28 pe�as do domin� (de 0|0 at� 6|6)
void gerarPecas();

//Vari�veis globais
int jogadorAtual; 	//Indica o jogador da vez: 1 = Jogador 1, 2 = Jogador 2
int mesaD, mesaE;	//Extremidades Esquerda e Direita da mesa
int qtMesa; 		//Quantidade de pecas na mesa
int Jogar;

//Estruturas de dados principais
struct Mesa
{
	int ladoE;
	int ladoD;
	char status; //'J', 'N'
} mesa[28];			//Vetor representando at� 28 pe�as que podem estar na mesa


struct Peca {
	int ladoA;
	int ladoB;
	char status;	//NULL, '1', '2', 'M'
					//NULL = Dispon�vel, 1= com jogador 1, 2 = com o jogador 2
} pecas[28];		//Vetor com as 28 pe�as poss�veis do domin�

