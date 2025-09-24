//DOM-KLRR-MODEL.h - Projeto Dominó
//23/09/2025 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include <time.h>	//Necessário pois contém a variável NULL

//Gera todas as 28 peças do dominó (de 0|0 até 6|6)
void gerarPecas();

//Variáveis globais
int maquina;  		//Indica se a máquina está jogando (1 = sim, 0 = não)
int jogadorAtual; 	//Indica o jogador da vez: 1 = Jogador 1, 2 = Jogador 2
int mesaD, mesaE;	//Extremidades Esquerda e Direita da mesa
int qtMesa; 		//Quantidade de pecas na mesa

//Estruturas de dados principais
struct Mesa
{
	int ladoE;
	int ladoD;
	char status; 	//'J', 'N'
} mesa[28];		 	//Vetor representando até 28 peças que podem estar na mesa


struct Peca {
	int ladoA;
	int ladoB;
	char status;	//NULL, '1', '2', 'M'
					//NULL = Disponível, 1 = com jogador 1, 2 = com o jogador 2
} pecas[28];		//Vetor com as 28 peças possíveis do dominó

