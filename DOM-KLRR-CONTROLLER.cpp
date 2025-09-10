//DOM-KLRR-CONTROLLER.cpp - Projeto Dominó
//**/**/2025 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include "DOM-KLRR-CONTROLLER.h"
#include "DOM-KLRR-VIEW.cpp"

//Carrega um jogo salvo a partir de um arquivo
void carregarJogo() {
    FILE *fp;

    if ((fp = fopen("domino.dat", "r")) == NULL) {
    	printf("\n-------NENHUM JOGO SALVO ENCONTRADO!-------\n");
        Sleep(1000);
        return;
    }

    //Le o estado completo do jogo
    if (fread(&pecas, sizeof(pecas), 1, fp) != 1) { printf("Erro na leitura do estado das pecas.\n"); fclose(fp); return; }
    if (fread(&mesa, sizeof(mesa), 1, fp) != 1) { printf("Erro na leitura do estado da mesa.\n"); fclose(fp); return; }
    if (fread(&jogadorAtual, sizeof(int), 1, fp) != 1) { printf("Erro na leitura do jogador atual.\n"); fclose(fp); return; }
    if (fread(&qtMesa, sizeof(int), 1, fp) != 1) { printf("Erro na leitura da quantidade de pecas na mesa.\n"); fclose(fp); return; }
    if (fread(&mesaE, sizeof(int), 1, fp) != 1) { printf("Erro na leitura da extremidade esquerda.\n"); fclose(fp); return; }
    if (fread(&mesaD, sizeof(int), 1, fp) != 1) { printf("Erro na leitura da extremidade direita.\n"); fclose(fp); return; }

    fclose(fp);
    printf("\n-------JOGO CARREGADO COM SUCESSO!-------\n");
    Sleep(1000);
    
    //Apresenta o jogo carregado e entra no loop principal
    limparTela();
    apresentarMesa();
    iniciarJogo();
    
    do {
        menuJogador();
    
        switch(op2) {
            case('J'):
                fJ();				
				break;
        
            case('C'):	
                fC();
            	break;
    
            case('P'):
                fP();
                break;
    
            case('S'):
                limparTela();
                break;
        }
    } while (op2 != 'S');
}

//Embaralha as peças de dominó
void embaralhar() {
	srand(time(0));						//Inicializa o gerador de números aleatórios
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
    						fJ();
							break;
					
						case('C'):	
							fC();
							break;
				
						case('P'):
							fP();
							break;
				
						case('S'):
							limparTela();
							break;
					}
				} while (op2 != 'S');
				
				limparTela();
						
				break;
			
			case('2'): 
				prepararJogo();
					
					do {
						menuJogador();
					
						switch(op2) {
							case('J'): 
								fJ();	
								break;
						
							case('C'):	
								fC();
								break;
					
							case('P'):
								fP();
								cJogar();
								break;
					
							case('S'):
								limparTela();
								break;
						}
				} while (op2 != 'S');
					
				limparTela();
							
				break;
			
			case('3'): 
				printf("\n-----------RETORNANDO AO JOGO!-----------\n");
   				Sleep(1000);
				apresentarMesa();
				iniciarJogo();
				
				do {
					menuJogador();
				
					switch(op2) {
						case('J'): 
							fJ();
							break;
					
						case('C'):	
							fC();
							break;
				
						case('P'):
							fP();
							break;
				
						case('S'):
							limparTela();
							break;
					}
				} while (op2 != 'S');
				
				limparTela();
						
				break;
			
			case('4'): 
				limparTela();
				regras();
				break;
		
			case('5'): 
				salvarJogo();
				break;
		
			case('6'): 
				carregarJogo();
				break;
		
			case('0'):
				break;
		}
		
		limparTela();
	} while (op1 != '0');
}

void fJ() {
	jogarNaMesa();						
	Sleep(500);
	fclear();
	
	if (Jogar == 1) {
		trocarJogador();
	}							
}

void fC() {
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
	
	ganhador();
	
	limparTela();
	apresentarMesa();
	iniciarJogo();
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
	
	printf("\n------------------------------------\n");
	printf("|O jogador %d fez o primeiro lance. |\n", jogadorAtual);
	printf("------------------------------------\n");
	
	Sleep(1000);
	
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
	int r = 0, i = 0;				
	while (r == 0) {
		if(mesa[i].status == 'N') {
			mesaD = mesa[i - 1].ladoD;
			r = 1;
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
				printf("%d.[%d|%d]  ", i, pecas[i].ladoA, pecas[i].ladoB);
			}
		}
	}
	
	else {
		printf("JOGADOR 2\n");
		for (int i = 0; i < 28; i++) {
			if (pecas[i].status == '2') {
				printf("%d.[%d|%d]  ", i, pecas[i].ladoA, pecas[i].ladoB);
			}
		}
	}
	
	printf("\n");
}

void jogarNaMesa() {
	int i, ladoEsquerdo = 0, ladoDireito = 0;
	char lado;
	
	//Solicita o índice da peça que o jogador deseja jogar
	printf("Indice da peca selecionada: ");
	scanf(" %d", &i);
	
	//Verifica se a peça pode ser jogada no lado esquerdo da mesa
	if (pecas[i].ladoA == mesaE || pecas[i].ladoB == mesaE) {
		ladoEsquerdo = 1;
		Jogar = 1;
	}
		
	//Verifica se a peça pode ser jogada no lado direito da mesa
	if (pecas[i].ladoA == mesaD || pecas[i].ladoB == mesaD) {
		ladoDireito = 1;
		Jogar = 1;
	}
	
	//Se a peça não encaixa em nenhum lado, é inválida	
	if (ladoEsquerdo == 0 && ladoDireito == 0) {
		printf("\n--------------PECA INVALIDA!--------------");
		Jogar = 0;
		Sleep(500);
	}

	//Peça só pode ser jogada no lado direito
	if (ladoEsquerdo == 0 && ladoDireito == 1) {
		//Ajusta a peça para o lado certo
		if (pecas[i].ladoA == mesaD) {
			mesa[qtMesa].ladoE = pecas[i].ladoA;
			mesa[qtMesa].ladoD = pecas[i].ladoB;
			mesaD = pecas[i].ladoB;
		}
		
		else {
			mesa[qtMesa].ladoE = pecas[i].ladoB;
			mesa[qtMesa].ladoD = pecas[i].ladoA;
			mesaD = pecas[i].ladoA;
		}
		
		mesa[qtMesa].status = 'J';
		pecas[i].status = 'M';
		qtMesa++;
	}
	
	//Peça só pode ser jogada no lado esquerdo
	else if (ladoEsquerdo == 1 && ladoDireito == 0) {
		//Move todas as peças para a direita para abrir espaço na esquerda
		for (int j = qtMesa; j > 0; j--) {
			mesa[j].ladoD = mesa[j - 1].ladoD;
			mesa[j].ladoE = mesa[j - 1].ladoE;
			
			if (mesa[j - 1].status == 'J') {
				mesa[j].status = 'J';
			}
		}
		
		//Posiciona a nova peça na posição 0 (início da mesa)
		if (pecas[i].ladoA == mesaE) {
			mesa[0].ladoE = pecas[i].ladoB;
			mesa[0].ladoD = pecas[i].ladoA;
			mesaE = pecas[i].ladoB;
		}
		
		else {
			mesa[0].ladoE = pecas[i].ladoA;
			mesa[0].ladoD = pecas[i].ladoB;
			mesaE = pecas[i].ladoA;
		}
		
		mesa[qtMesa].status = 'J';
		pecas[i].status = 'M';
		qtMesa++;
	}
	
	//Peça pode ser jogada dos dois lados — jogador escolhe
	else if (ladoEsquerdo == 1 && ladoDireito == 1) {
		printf("Qual lado? (D - Direito, E - Esquerdo): ");
		scanf(" %c", &lado);
		lado = toupper(lado);
	
		//Jogar à direita
		if (lado == 'D') {
			if (pecas[i].ladoA == mesaD) {
				mesa[qtMesa].ladoE = pecas[i].ladoA;
				mesa[qtMesa].ladoD = pecas[i].ladoB;
				mesaD = pecas[i].ladoB;
			}
		
			else {
				mesa[qtMesa].ladoE = pecas[i].ladoB;
				mesa[qtMesa].ladoD = pecas[i].ladoA;
				mesaD = pecas[i].ladoA;
			}
			
			mesa[qtMesa].status = 'J';
			pecas[i].status = 'M';
			qtMesa++;
		}
		
		//Jogar à esquerda
		else if (lado == 'E'){
			for (int j = qtMesa; j > 0; j--) {
				mesa[j].ladoD = mesa[j - 1].ladoD;
				mesa[j].ladoE = mesa[j - 1].ladoE;
				
				if (mesa[j - 1].status == 'J') {
					mesa[j].status = 'J';
				}
			}
			
			if (pecas[i].ladoA == mesaE) {
				mesa[0].ladoE = pecas[i].ladoB;
				mesa[0].ladoD = pecas[i].ladoA;
				mesaE = pecas[i].ladoB;
			}
			
			else {
				mesa[0].ladoE = pecas[i].ladoA;
				mesa[0].ladoD = pecas[i].ladoB;
				mesaE = pecas[i].ladoA;
			}
			
			mesa[qtMesa].status = 'J';
			pecas[i].status = 'M';
			qtMesa++;
		}
		
		else {
			printf("\n--------------LADO INVALIDO!--------------");
			Jogar = 0;
			Sleep(500);
		}
	}
	
	//Verifica se há ganhador após a jogada
	ganhador();
}

void fP() {
	//Verifica se o jogo foi ganho antes de passar
	ganhador();
	
	//Passar se ele nao tiver nenhuma peça para jogar e nao tiver mais peca para comprar
	int j = 0, l = 0;
	char k;
	
	//Define o jogador atual como '1' ou '2'
	if (jogadorAtual == 1) {
		k = '1';
	}
	
	else {
		k = '2';
	}
	
	//Verifica se o jogador atual possui jogadas possíveis
	for (int i = 0; i < 28; i++) { 
		if (pecas[i].status == k) {
			if ((pecas[i].ladoA == mesaE || pecas[i].ladoA == mesaD) || (pecas[i].ladoB == mesaE || pecas[i].ladoB == mesaD)) {
				j = 1;
			}
		}		
	}
	
	//Verifica se ainda existem peças no monte para comprar
	for (int i = 0; i < 28; i++) {
		if (pecas[i].status == 0) {
			l = 1;
		}
	}
	
	//Se não há jogadas nem peças para comprar: passa o turno
	if (j == 0 && l == 0) {
		limparTela();
		trocarJogador();
		apresentarMesa();
		iniciarJogo();
	}
	
	else if (j == 1){
		printf("\n--------------HA JOGADAS POSSIVEIS!--------------\n");
		Sleep(500);
	}
	
	else {
		printf("\n--------------HA PECAS PARA COMPRAR!--------------\n");
		Sleep(500);
	}
}

void ganhador() {
	int pecasJ1 = 0;
	int pecasJ2 = 0;
	int j = 0, l = 0;
	int j1 = 0, j2 = 0;
	
	//Conta peças ainda na mão dos jogadores
	for (int i = 0; i < 28; i++) {
		if (pecas[i].status == '1') {
			pecasJ1 = pecasJ1 + 1;
		}
		
		else if (pecas[i].status == '2') {
			pecasJ2 = pecasJ2 + 1;
		}
	}
	
	//Verifica se ainda existem jogadas possíveis na mesa
	for (int i = 0; i < 28; i++) { 
		if (pecas[i].status == '1' || pecas[i].status == '2') {
			if ((pecas[i].ladoA == mesaE || pecas[i].ladoA == mesaD) || (pecas[i].ladoB == mesaE || pecas[i].ladoB == mesaD)) {
				j = 1;
			}
		}		
	}
	
	//Verifica se ainda existem peças para comprar
	for (int i = 0; i < 28; i++) {
		if (pecas[i].status == 0) {
			l = 1;
		}
	}
	
	//Se algum jogador ficou sem peças, vence
	if (pecasJ1 == 0) {
		limparTela();
		printf("\n---------O JOGADOR 1 VENCEU O JOGO---------\n");
		Sleep(2000);
		op2 = 'S';
	}
	
	else if (pecasJ2 == 0) {
		limparTela();
		printf("\n---------O JOGADOR 2 VENCEU O JOGO---------\n");
		Sleep(2000);
		op2 = 'S';
	}	
	
	//Se nao for possivel mais jogar ou comprar pecas, vence aquele que tiver menos pecas
	else if (j == 0 && l == 0) {
		if (pecasJ2 > pecasJ1) {
			limparTela();
			printf("\n---------O JOGADOR 1 VENCEU O JOGO---------\n");
			Sleep(2000);
			op2 = 'S';
		}
		
		else if (pecasJ1 > pecasJ2) {
			limparTela();
			printf("\n---------O JOGADOR 2 VENCEU O JOGO---------\n");
			Sleep(2000);
			op2 = 'S';
		}
		
		else {
			//Caso o número de peças restantes seja igual, soma os valores das peças
			for (int i = 0; i < 28; i++) {
				if (pecas[i].status == '1') {
					j1 = j1 + pecas[i].ladoA + pecas[i].ladoB;
				}
				
				else if (pecas[i].status == '2') {
					j2 = j2 + pecas[i].ladoA + pecas[i].ladoB;
				}
			}
			
			//Compara a soma dos valores das peças para decidir o vencedor
			if (j2 > j1) {
				limparTela();
				printf("\n---------O JOGADOR 1 VENCEU O JOGO---------\n");
				Sleep(2000);
				op2 = 'S';
			}
			
			else if (j1 > j2) {
				limparTela();
				printf("\n---------O JOGADOR 2 VENCEU O JOGO---------\n");
				Sleep(2000);
				op2 = 'S';
			}
			
			else {
				limparTela();
				printf("\n---------O JOGO DEU EMPATE---------\n");
				Sleep(2000);
				op2 = 'S';
			}
		}
	}
}

void cJogar() {
	int i, ladoEsquerdo = 0, ladoDireito = 0;
	char lado;
	
	for (i = 0; i < 28; i++) {
		if (pecas[i].status == '2') {
			//Verifica se a peça pode ser jogada no lado esquerdo da mesa
			if (pecas[i].ladoA == mesaE || pecas[i].ladoB == mesaE) {
				ladoEsquerdo = 1;
				Jogar = 1;
			}
				
			//Verifica se a peça pode ser jogada no lado direito da mesa
			else if (pecas[i].ladoA == mesaD || pecas[i].ladoB == mesaD) {
				ladoDireito = 1;
				Jogar = 1;
			}
			
			else {
				Jogar = 0;
			}
		
			//Peça só pode ser jogada no lado direito
			if (ladoEsquerdo == 0 && ladoDireito == 1) {
				//Ajusta a peça para o lado certo
				if (pecas[i].ladoA == mesaD) {
					mesa[qtMesa].ladoE = pecas[i].ladoA;
					mesa[qtMesa].ladoD = pecas[i].ladoB;
					mesaD = pecas[i].ladoB;
				}
				
				else {
					mesa[qtMesa].ladoE = pecas[i].ladoB;
					mesa[qtMesa].ladoD = pecas[i].ladoA;
					mesaD = pecas[i].ladoA;
				}
				
				mesa[qtMesa].status = 'J';
				pecas[i].status = 'M';
				qtMesa++;
				break;
			}
			
			//Peça só pode ser jogada no lado esquerdo
			else if (ladoEsquerdo == 1 && ladoDireito == 0) {
				//Move todas as peças para a direita para abrir espaço na esquerda
				for (int j = qtMesa; j > 0; j--) {
					mesa[j].ladoD = mesa[j - 1].ladoD;
					mesa[j].ladoE = mesa[j - 1].ladoE;
					
					if (mesa[j - 1].status == 'J') {
						mesa[j].status = 'J';
					}
				}
				
				//Posiciona a nova peça na posição 0 (início da mesa)
				if (pecas[i].ladoA == mesaE) {
					mesa[0].ladoE = pecas[i].ladoB;
					mesa[0].ladoD = pecas[i].ladoA;
					mesaE = pecas[i].ladoB;
				}
				
				else {
					mesa[0].ladoE = pecas[i].ladoA;
					mesa[0].ladoD = pecas[i].ladoB;
					mesaE = pecas[i].ladoA;
				}
				
				mesa[qtMesa].status = 'J';
				pecas[i].status = 'M';
				qtMesa++;
				break;
			}
			
			//Peça pode ser jogada dos dois lados — jogador escolhe
			else if (ladoEsquerdo == 1 && ladoDireito == 1) {	
				//Jogar à direita
				if (lado == 'D') {
					if (pecas[i].ladoA == mesaD) {
						mesa[qtMesa].ladoE = pecas[i].ladoA;
						mesa[qtMesa].ladoD = pecas[i].ladoB;
						mesaD = pecas[i].ladoB;
					}
				
					else {
						mesa[qtMesa].ladoE = pecas[i].ladoB;
						mesa[qtMesa].ladoD = pecas[i].ladoA;
						mesaD = pecas[i].ladoA;
					}
					
					mesa[qtMesa].status = 'J';
					pecas[i].status = 'M';
					qtMesa++;
					break;
				}
			}
		}
	}
	
	if (Jogar == 0) {
		for (int i = 14; i < 28; i++) {
			if (pecas[i].status == 0) {
				if (jogadorAtual == 2) {
					pecas[i].status = '2';
				}
										
				else {
					pecas[i].status = '2';
				}
										
				break;
			}
		}
							
		ganhador();
							
		limparTela();
		apresentarMesa();
		iniciarJogo();		
	}				
}

//Salva o estado atual do jogo em um arquivo
void salvarJogo() {
    FILE *fp;

    if ((fp = fopen("domino.dat", "w")) == NULL) {
        printf("\nErro: O arquivo nao pode ser aberto para gravacao.\n");
        Sleep(1000);
        return;
    }

    //Grava o estado completo do jogo (structs e variaveis de controle)
    if (fwrite(&pecas, sizeof(pecas), 1, fp) != 1) { printf("Erro na gravacao do estado das pecas.\n"); fclose(fp); return; }
    if (fwrite(&mesa, sizeof(mesa), 1, fp) != 1) { printf("Erro na gravacao do estado da mesa.\n"); fclose(fp); return; }
    if (fwrite(&jogadorAtual, sizeof(int), 1, fp) != 1) { printf("Erro na gravacao do jogador atual.\n"); fclose(fp); return; }
    if (fwrite(&qtMesa, sizeof(int), 1, fp) != 1) { printf("Erro na gravacao da quantidade de pecas na mesa.\n"); fclose(fp); return; }
    if (fwrite(&mesaE, sizeof(int), 1, fp) != 1) { printf("Erro na gravacao da extremidade esquerda.\n"); fclose(fp); return; }
    if (fwrite(&mesaD, sizeof(int), 1, fp) != 1) { printf("Erro na gravacao da extremidade direita.\n"); fclose(fp); return; }

    fclose(fp);
    printf("\n----------JOGO SALVO COM SUCESSO!----------\n");
    Sleep(1000);
}
