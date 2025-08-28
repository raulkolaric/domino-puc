//DOM-KLRR-CONTROLLER.cpp - Projeto Dominó
//26/08/25 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include "DOM-KLRR-CONTROLLER.h"
#include "DOM-KLRR-VIEW.cpp"

//Ebaralha as peças de dominó
void embaralhar() {
	srand(time(0));						// Inicializa o gerador de números aleatórios
	int n = 28;			
	struct Peca temp;
	for(int i = n - 1; i > 0; i--) {
		int j = rand()%(n);
		temp = pecas[i];
		pecas[i] = pecas[j];
		pecas[j] = temp;
	}
}

//Função principal de controle das jogadas e menus
void jogar() {
	do {
		menuInicial();
	
		switch (op1) {
			case('1'): 
				prepararJogo();
				
				do {
					menuJogador();
				
					switch(op2) {
						case('J'):
							
							limparTela();
							break;
					
						case('C'):	
							for (int i = 14; i < 28; i++) {
								if (pecas[i].status == 0) {
									if (jogadorAtual == 1) {
										pecas[i].status = '1';
									}
									
									else {
										pecas[i].status = '2';
									}
									
									break;
								}
							}
							
							limparTela();
							apresentarMesa();
							iniciarJogo();
						
							break;
				
						case('P'):
							limparTela();
							trocarJogador();
							apresentarMesa();
							iniciarJogo();
							break;
				
						case('S'):
							limparTela();
							break;
					}
				} while (op2 != 'S');
				
				limparTela();
						
				break;
			
			case('2'): 
			
				break;
			
			case('3'): 
			
				break;
			
			case('4'): 
				limparTela();
				regras();
		
				break;
		
			case('5'): 
			
				break;
		
			case('6'): 
	
				break;
		
			case('0'):
				break;
		}
		
		limparTela();
	} while (op1 != '0');
}

//Prepara o início do jogo: embaralha, distribui peças e define quem joga primeiro
void prepararJogo() {
	embaralhar();
	
	//Inicializa peças e mesa
	for (int i = 0; i < 28 ; i++) {
		pecas[i].status = 0;
		mesa[i].ladoD = -1;
		mesa[i].ladoE = -1;
		mesa[i].status = 'N';
	}
	
	//Distribui peças para jogador 1
	for (int i = 0; i < 7; i++) {
		pecas[i].status = '1';
	}
	
	//Distribui peças para jogador 2
	for (int i = 7; i < 14 ; i++) {
		pecas[i].status = '2';
	}
	
	primeiroLance();
	
	limparTela();
	
	printf("O jogador %d fez o primeiro lance.\n\n", jogadorAtual);
	
	apresentarMesa();
	
	trocarJogador();
	
	iniciarJogo();
}

//Define quem será o primeiro a jogar - Critério: maior duplo ou, se não houver, maior soma
int primeiroLance() {
	int j = -1, k;										// j = valor da maior peça encontrada, k = índice
	
	//Procura o maior duplo (ex: 6-6, 5-5, etc.)
	for (int i = 0; i < 14; i++) {
		if (pecas[i].ladoA == pecas[i].ladoB) {
			if((pecas[i].ladoA + pecas[i].ladoB) > j) {
				j = pecas[i].ladoA + pecas[i].ladoB;
				k = i;
			}
		}
	}
	
	//Caso nenhum duplo tenha sido encontrado
	if (j == -1) {
		for (int i = 0; i < 14; i++) {
			if((pecas[i].ladoA + pecas[i].ladoB) > j) {
				j = pecas[i].ladoA + pecas[i].ladoB;
				k = i;
			}
		}
	}
	
	//Coloca a peça escolhida na mesa
	mesa[0].ladoE = pecas[k].ladoA;
	mesa[0].ladoD = pecas[k].ladoB;
	mesa[0].status = 'J';
	pecas[k].status = 'M';
	qtMesa = 1;
	
	//Define quem foi o jogador que colocou a peça
	if (k < 7) {
		jogadorAtual = 1;	
	}
	
	else {
		jogadorAtual = 2;
	}
	
	mesaE = mesa[0].ladoE;	
	int r=0,i=0;				
	while(r==0) {
		if(mesa[i].status == 'N') {
			mesaD=mesa[i-1].ladoD;
			r=1;
		}
		i++;
	}
	
	return jogadorAtual;
}

//Alterna entre jogador 1 e jogador 2
void trocarJogador() {
	
	if (jogadorAtual == 1) {
		jogadorAtual = 2;
	}
	
	else {
		jogadorAtual = 1;
	}
		
}

//Mostra as peças do jogador atual na tela
void iniciarJogo() {
	printf("\n");
	
	if (jogadorAtual == 1) {
		printf("JOGADOR 1\n");
		
		for (int i = 0; i < 28; i++) {
			if (pecas[i].status == '1') {
				printf("[%d|%d] ", pecas[i].ladoA, pecas[i].ladoB);
			}
		}
	}
	
	else {
		printf("JOGADOR 2\n");
		for (int i = 0; i < 28; i++) {
			if (pecas[i].status == '2') {
				printf("[%d|%d] ", pecas[i].ladoA, pecas[i].ladoB);
			}
		}
	}
	
	printf("\n");
}
