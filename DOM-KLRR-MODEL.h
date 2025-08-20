//DOM-KLRR-MODEL.h - Projeto Domin�
//##-08-25 - Grupo: KLRR
//Kau� Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

//Vari�veis globais
int mesaE, mesaD;	//Extremidades Esquerda e Direita da mesa
int qtmesa; //qtde de pecas na mesa
char jogadoratual;

//Estrutura das pe�as
struct Peca {
	int ladoA;
	int ladoB;
	char status;	//NULL, '1', '2', 'M'
					//NULL = Dispon�vel, 1= com jogador 1, 2 = com o jogador 2
} pecas[28];

struct Mesa
{
	int ladoE;
	int ladoD;
} mesa[28];

void GerarPecas();