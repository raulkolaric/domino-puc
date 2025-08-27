//DOM-KLRR-CONTROLLER.cpp - Projeto Domin�
//26/08/25 - Grupo: KLRR
//Kau� Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include "DOM-KLRR-CONTROLLER.h"
#include "DOM-KLRR-VIEW.cpp"

//Ebaralha as pe�as de domin�
void embaralhar() {
	srand(time(0));						// Inicializa o gerador de n�meros aleat�rios
	int n = 28;			
	struct Peca temp;
	for(int i = n - 1; i > 0; i--) {
		int j = rand()%(n);
		temp = pecas[i];
		pecas[i] = pecas[j];
		pecas[j] = temp;
	}
}

//Fun��o principal de controle das jogadas e menus
void jogar() {
	menuInicial();
	
	switch (op1) {
		case('1'): 
			prepararJogo();
			
			menuJogador();
			
			switch(op2) {
				case('J'):
					//selecionar pe�a 
					break;
				
				case('C'):
					
					break;
				
				case('P'):
					
					break;
				
				case('S'):
					break;
			}
						
			break;
			
		case('2'): 
			
			break;
			
		case('3'): 
			
			break;
			
		case('4'): 
			regras();
		
			break;
		
		case('5'): 
			
			break;
		
		case('6'): 
	
			break;
		
		case('0'):
			break;
	}
}

//Prepara o in�cio do jogo: embaralha, distribui pe�as e define quem joga primeiro
void prepararJogo() {
	embaralhar();
	
	//Inicializa pe�as e mesa
	for (int i = 0; i < 28 ; i++) {
		pecas[i].status = 0;
		mesa[i].ladoD = -1;
		mesa[i].ladoE = -1;
		mesa[i].status = 'N';
	}
	
	//Distribui pe�as para jogador 1
	for (int i = 0; i < 7; i++) {
		pecas[i].status = '1';
	}
	
	//Distribui pe�as para jogador 2
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

//Define quem ser� o primeiro a jogar - Crit�rio: maior duplo ou, se n�o houver, maior soma
int primeiroLance() {
	int j = 0, k;										// j = valor da maior pe�a encontrada, k = �ndice
	
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
	if (j == 0) {
		for (int i = 0; i < 14; i++) {
			if((pecas[i].ladoA + pecas[i].ladoB) > j) {
				j = pecas[i].ladoA + pecas[i].ladoB;
				k = i;
			}
		}
	}
	
	//Coloca a pe�a escolhida na mesa
	mesa[0].ladoE = pecas[k].ladoA;
	mesa[0].ladoD = pecas[k].ladoB;
	mesa[0].status = 'J';
	pecas[k].status = 'M';
	qtMesa = 1;
	
	//Define quem foi o jogador que colocou a pe�a
	if (k < 7) {
		jogadorAtual = 1;	
	}
	
	else {
		jogadorAtual = 2;
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

//Mostra as pe�as do jogador atual na tela
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
