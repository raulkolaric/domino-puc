//DOM-KLRR-CONTROLLER.cpp - Projeto Domin�
//23/09/2025 - Grupo: KLRR
//Kau� Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include "DOM-KLRR-CONTROLLER.h"
#include "DOM-KLRR-VIEW.cpp"

//Carrega o estado do jogo a partir de um arquivo "domino.dat"
//Inclui verifica��o de erros na leitura e mant�m o loop do menu de jogadas.
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
    if (fread(&maquina, sizeof(int), 1, fp) != 1) { printf("Erro na leitura da maquina.\n"); fclose(fp); return; }

    fclose(fp);
    
    //Apresenta o jogo carregado e entra no loop principal
    printf("\n-------JOGO CARREGADO COM SUCESSO!-------\n");
    Sleep(1000);
    
    do {
        menuJogador();
    
        switch(op2) {
            case('J'):
                fJogar();				
				break;
        
            case('C'):	
                fComprar();
            	break;
    
            case('P'):
                fPassar();
                break;
    
            case('S'):
                limparTela();
                break;
        }
    } while (op2 != 'S');
}

//jogador vs jogador
void caso1() {
	maquina = 0;
	prepararJogo();
	
	do {
		menuJogador();
	
		switch(op2) {
			case('J'): 
				fJogar();
				break;
		
			case('C'):	
				fComprar();
				break;
	
			case('P'):
				fPassar();
				break;
	
			case('S'):
				limparTela();
				break;
		}
	} while (op2 != 'S');
}

//jogador vs m�quina
void caso2() {
	maquina = 1;
	prepararJogo();
		
	do {
		menuJogador();
	
		switch(op2) {
			case('J'): 
				fJogar();
					
				break;
		
			case('C'):	
				fComprar();
				break;
	
			case('P'):
				fPassar();
				break;
	
			case('S'):
				limparTela();
				break;
		}
	} while (op2 != 'S');
}

//retomar jogo salvo
void caso3() {
	printf("\n-----------RETORNANDO AO JOGO!-----------\n");
	Sleep(1000);
	
	do {
		menuJogador();
	
		switch(op2) {
			case('J'): 
				fJogar();
				break;
		
			case('C'):	
				fComprar();
				break;
	
			case('P'):
				fPassar();
				break;
	
			case('S'):
				limparTela();
				break;
		}
	} while (op2 != 'S');
}

//Embaralha as pe�as de domin�
void embaralhar() {
	srand(time(0));						//Inicializa o gerador de n�meros aleat�rios
	int n = 28;			
	struct Peca temp;
	
	for(int i = n - 1; i > 0; i--) {
		int j = rand()%(n);
		temp = pecas[i];
		pecas[i] = pecas[j];
		pecas[j] = temp;
	}
}

//Permite que o jogador compre uma pe�a do monte (�ndices 14-27)
//Atualiza status da pe�a para o jogador atual
void fComprar() {
	int pecasComprar = 0;
	
	for (int i = 14; i < 28; i++) {
		if (pecas[i].status == 0) {
			pecasComprar = 1;
			
			if (jogadorAtual == 1) {
				pecas[i].status = '1';
			}
			
			else {
				pecas[i].status = '2';
			}

			break;
		}
	}
	
	if (pecasComprar == 0) {
		printf("\n---------NAO HA PECAS PARA COMPRAR!---------");	
		Sleep(500);
	}
	
	ganhador();
}

//Controla a jogada do jogador humano
//Valida �ndice e status da pe�a, verifica lados poss�veis e atualiza a mesa
//Evita jogar pe�as inv�lidas
void fJogar() {
	int jogadorJogou = 0;
	
	//Solicita o �ndice da pe�a que o jogador deseja jogar
	int indice;
	printf("Indice da peca selecionada: ");
	scanf(" %d", &indice);
	
	//Valida��o do �ndice
	if (indice < 0 || indice > 27) {
        printf("\n--------------INDICE INVALIDO!--------------\n");
        Sleep(500);	
        fclear();
        return;
    }
	
	//Valida��o da pe�a: deve pertencer ao jogador atual
	if ((jogadorAtual == 1 && pecas[indice].status != '1') || (jogadorAtual == 2 && pecas[indice].status != '2')) {
		printf("\n--------------PECA INVALIDA!--------------");
		Sleep(500);
		fclear();
		return;
	}
	
	//Verifica se a pe�a pode ser jogada no lado esquerdo da mesa
	int ladoEsquerdo = 0, ladoDireito = 0;
	if (pecas[indice].ladoA == mesaE || pecas[indice].ladoB == mesaE) {
		ladoEsquerdo = 1;
	}
		
	//Verifica se a pe�a pode ser jogada no lado direito da mesa
	if (pecas[indice].ladoA == mesaD || pecas[indice].ladoB == mesaD) {
		ladoDireito = 1;
	}
	
	//Pe�a pode ser jogada dos dois lados � jogador escolhe
	if (ladoEsquerdo == 1 && ladoDireito == 1) {
		char lado;
		printf("Qual lado? (D - Direito, E - Esquerdo): ");
		scanf(" %c", &lado);
		lado = toupper(lado);
	
		//Jogar � direita
		if (lado == 'D') {
			if (pecas[indice].ladoA == mesaD) {
				mesa[qtMesa].ladoE = pecas[indice].ladoA;
				mesa[qtMesa].ladoD = pecas[indice].ladoB;
				mesaD = pecas[indice].ladoB;
			}
		
			else {
				mesa[qtMesa].ladoE = pecas[indice].ladoB;
				mesa[qtMesa].ladoD = pecas[indice].ladoA;
				mesaD = pecas[indice].ladoA;
			}
			
			mesa[qtMesa].status = 'J';
			pecas[indice].status = 'M';
			qtMesa++;
			jogadorJogou = 1;
		}
		
		//Jogar � esquerda
		else if (lado == 'E'){
			for (int i = qtMesa; i > 0; i--) {
				mesa[i] = mesa[i - 1];
			}
			
			if (pecas[indice].ladoA == mesaE) {
				mesa[0].ladoE = pecas[indice].ladoB;
				mesa[0].ladoD = pecas[indice].ladoA;
				mesaE = pecas[indice].ladoB;
			}
			
			else {
				mesa[0].ladoE = pecas[indice].ladoA;
				mesa[0].ladoD = pecas[indice].ladoB;
				mesaE = pecas[indice].ladoA;
			}
			
			pecas[indice].status = 'M';
			qtMesa++;
			jogadorJogou = 1;
		}
		
		else {
			printf("\n--------------LADO INVALIDO!--------------");
			Sleep(500);
			return;
		}
	}

	//Pe�a s� pode ser jogada no lado direito
	else if (ladoDireito == 1) {
		//Ajusta a pe�a para o lado certo
		if (pecas[indice].ladoA == mesaD) {
			mesa[qtMesa].ladoE = pecas[indice].ladoA;
			mesa[qtMesa].ladoD = pecas[indice].ladoB;
			mesaD = pecas[indice].ladoB;
		}
		
		else {
			mesa[qtMesa].ladoE = pecas[indice].ladoB;
			mesa[qtMesa].ladoD = pecas[indice].ladoA;
			mesaD = pecas[indice].ladoA;
		}
		
		mesa[qtMesa].status = 'J';
		pecas[indice].status = 'M';
		qtMesa++;
		jogadorJogou = 1;
	}
	
	//Pe�a s� pode ser jogada no lado esquerdo
	else if (ladoEsquerdo == 1) {
		//Move todas as pe�as para a direita para abrir espa�o na esquerda
		for (int i = qtMesa; i > 0; i--) {
			mesa[i] = mesa[i - 1];
		}
		
		if (pecas[indice].ladoA == mesaE) {
			mesa[0].ladoE = pecas[indice].ladoB;
			mesa[0].ladoD = pecas[indice].ladoA;
			mesaE = pecas[indice].ladoB;
		}
		
		else {
			mesa[0].ladoE = pecas[indice].ladoA;
			mesa[0].ladoD = pecas[indice].ladoB;
			mesaE = pecas[indice].ladoA;
		}
		
		pecas[indice].status = 'M';
		qtMesa++;
		jogadorJogou = 1;
	}
	
	//Se a pe�a n�o encaixa em nenhum lado, � inv�lida	
	else {
		printf("\n--------------PECA INVALIDA!--------------");
		Sleep(500);
		return;
	}
	
	Sleep(500);
	fclear();
	
	//Ap�s jogada, verifica ganhador e passa vez ou executa m�quina
	if (jogadorJogou == 1) {
		ganhador();	
		
		if (maquina == 0) {
			trocarJogador();
		}
		
		else {
			maquinaJogar();
		}
	}
}

//Permite que o jogador passe a vez se n�o houver jogadas poss�veis
//Se n�o houver pe�as para comprar, troca jogador automaticamente
void fPassar() {
	//Verifica se o jogador atual possui jogadas poss�veis
	int haPecasParaJogar = 0;
	for (int i = 0; i < 28; i++) { 
		if ((jogadorAtual == 1 && pecas[i].status == '1') || (jogadorAtual == 2 && pecas[i].status == '2')) {
			if ((pecas[i].ladoA == mesaE || pecas[i].ladoA == mesaD) || (pecas[i].ladoB == mesaE || pecas[i].ladoB == mesaD)) {
				haPecasParaJogar = 1;
				break;
			}
		}		
	}
	
	//Verifica se ainda existem pe�as no monte para comprar
	int haPecasParaComprar = 0;
	for (int i = 0; i < 28; i++) {
		if (pecas[i].status == 0) {
			haPecasParaComprar = 1;
			break;
		}
	}
	
	if (haPecasParaJogar == 1) {
		printf("\n--------------HA JOGADAS POSSIVEIS!--------------\n");
		Sleep(500);
		return;
	}
	
	else if (haPecasParaComprar == 1) {
		printf("\n--------------HA PECAS PARA COMPRAR!--------------\n");
		Sleep(500);
		return;
	}
	
	else {
		ganhador();
		
		if (maquina == 0) {
			trocarJogador();
		}
		
		else {
			maquinaJogar();
		}
	}
}

//Verifica se algum jogador venceu
void ganhador() {
	//Conta pe�as ainda na m�o dos jogadores
	int pecasJ1 = 0, pecasJ2 = 0;
	int somaPecasJ1 = 0, somaPecasJ2 = 0;
	for (int i = 0; i < 28; i++) {
		if (pecas[i].status == '1') {
			pecasJ1++;
			somaPecasJ1 += pecas[i].ladoA + pecas[i].ladoB;
		}
		
		else if (pecas[i].status == '2') {
			pecasJ2++;
			somaPecasJ2 += pecas[i].ladoA + pecas[i].ladoB;
		}
	}
	
	//Verifica se ainda existem jogadas poss�veis na mesa
	int haPecasParaJogar = 0, haPecasParaComprar = 0;
	for (int i = 0; i < 28; i++) { 
		if (pecas[i].status == '1' || pecas[i].status == '2') {
			if ((pecas[i].ladoA == mesaE || pecas[i].ladoA == mesaD) || (pecas[i].ladoB == mesaE || pecas[i].ladoB == mesaD)) {
				haPecasParaJogar = 1;
			}
		}
		
		else if (pecas[i].status == 0) {
			haPecasParaComprar = 1;
		}		
	}
	
	//Se algum jogador ficou sem pe�as, vence
	if (pecasJ1 == 0) {
		limparTela();
		printf("\n---------O JOGADOR 1 VENCEU O JOGO---------\n");
		Sleep(2000);
		op2 = 'S';
		return;
	}
	
	else if (pecasJ2 == 0) {
		limparTela();
		printf("\n---------O JOGADOR 2 VENCEU O JOGO---------\n");
		Sleep(2000);
		op2 = 'S';
		return;
	}
	
	//Se nao for possivel mais jogar ou comprar pecas, vence aquele que tiver menos pecas
	if (haPecasParaJogar == 0 && haPecasParaComprar == 0) {
		limparTela();
		
		if (pecasJ2 > pecasJ1) {
			printf("\n---------O JOGADOR 1 VENCEU O JOGO---------\n");
		}
		
		else if (pecasJ1 > pecasJ2) {
			printf("\n---------O JOGADOR 2 VENCEU O JOGO---------\n");
		}
		
		else {
			//Compara a soma dos valores das pe�as para decidir o vencedor
			if (somaPecasJ1 < somaPecasJ2) {
				printf("\n---------O JOGADOR 1 VENCEU O JOGO---------\n");
			}
			
			else if (somaPecasJ2 < somaPecasJ1) {
				printf("\n---------O JOGADOR 2 VENCEU O JOGO---------\n");
			}
			
			else {
				printf("\n---------O JOGO DEU EMPATE---------\n");
			}
		}
		
		Sleep(2000);
		op2 = 'S';
	}
}

//Fun��o principal de controle das jogadas e menus
void jogar() {
	do {
		menuInicial();
	
		switch (op1) {
			case('1'): 
				caso1();
				break;
				
			case('2'): 
				caso2();
				break;
			
			case('3'): 
				caso3();	
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

//L�gica de jogada da m�quina
//Percorre pe�as da m�quina (�ndices 7-27), tenta jogar � direita ou esquerda
//Compra pe�a se n�o houver jogadas poss�veis
void maquinaJogar() {
	int maquinaJogou = 0;
	
	do {
		for (int indice = 7; indice < 28; indice++) {
			int ladoEsquerdo = 0, ladoDireito = 0;
			
			if (pecas[indice].status == '2') {
				//Verifica se a pe�a pode ser jogada no lado esquerdo da mesa
				if (pecas[indice].ladoA == mesaE || pecas[indice].ladoB == mesaE) {
					ladoEsquerdo = 1;
				}
					
				//Verifica se a pe�a pode ser jogada no lado direito da mesa
				if (pecas[indice].ladoA == mesaD || pecas[indice].ladoB == mesaD) {
					ladoDireito = 1;
				}
			
				//Pe�a pode ser jogada no lado direito
				if (ladoDireito == 1) {
					//Ajusta a pe�a para o lado certo
					if (pecas[indice].ladoA == mesaD) {
						mesa[qtMesa].ladoE = pecas[indice].ladoA;
						mesa[qtMesa].ladoD = pecas[indice].ladoB;
						mesaD = pecas[indice].ladoB;
					}
					
					else {
						mesa[qtMesa].ladoE = pecas[indice].ladoB;
						mesa[qtMesa].ladoD = pecas[indice].ladoA;
						mesaD = pecas[indice].ladoA;
					}
					
					mesa[qtMesa].status = 'J';
					pecas[indice].status = 'M';
					qtMesa++;
					maquinaJogou = 1;
					break;
				}
				
				//Pe�a pode ser jogada no lado esquerdo
				else if (ladoEsquerdo == 1) {
					//Move todas as pe�as para a direita para abrir espa�o na esquerda
					for (int i = qtMesa; i > 0; i--) {
						mesa[i] = mesa[i - 1];
					}
					
					//Posiciona a nova pe�a na posi��o 0 (in�cio da mesa)
					if (pecas[indice].ladoA == mesaE) {
						mesa[0].ladoE = pecas[indice].ladoB;
						mesa[0].ladoD = pecas[indice].ladoA;
						mesaE = pecas[indice].ladoB;
					}
					
					else {
						mesa[0].ladoE = pecas[indice].ladoA;
						mesa[0].ladoD = pecas[indice].ladoB;
						mesaE = pecas[indice].ladoA;
					}
					
					pecas[indice].status = 'M';
					qtMesa++;
					maquinaJogou = 1;
					break;
				}
			}
		}
		
		if (maquinaJogou == 0) {
		 	for (int i = 14; i < 28; i++) {
				if (pecas[i].status == 0) {
					pecas[i].status = '2';
					break;
				}
			}	
		}
		
		int haPecasParaComprar = 0;
		for (int i = 0; i < 28; i++) {
			if (pecas[i].status == 0) {
				haPecasParaComprar = 1;
				break;
			}
		}
		
		if (maquinaJogou == 1 || haPecasParaComprar == 0) {
			break;
		}
			
	} while (1);
	
	ganhador();			
}

//Mostra as pe�as do jogador atual na tela
void mostrarPecas() {
	printf("\nJOGADOR %d\n", jogadorAtual);
	
	if (jogadorAtual == 1) {		
		for (int i = 0; i < 28; i++) {
			if (pecas[i].status == '1') {
				printf("%d.[%d|%d]  ", i, pecas[i].ladoA, pecas[i].ladoB);
			}
		}
	}
	
	else {
		for (int i = 0; i < 28; i++) {
			if (pecas[i].status == '2') {
				printf("%d.[%d|%d]  ", i, pecas[i].ladoA, pecas[i].ladoB);
			}
		}
	}
	
	printf("\n");
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
		
		if (i < 7) {
			pecas[i].status = '1';
		}
		
		else if (i < 14) {
			pecas[i].status = '2';
		}
	}
	
	primeiroLance();
	 
	trocarJogador();
	
	if (jogadorAtual == 2 && maquina == 1) {
		trocarJogador();
		maquinaJogar();
	}
}

//Define quem ser� o primeiro a jogar - Crit�rio: maior duplo ou, se n�o houver, maior soma
void primeiroLance() {
	int maior = -1, indice;										
	
	//Procura o maior duplo (ex: 6-6, 5-5, etc.)
	for (int i = 0; i < 14; i++) {
		if (pecas[i].ladoA == pecas[i].ladoB) {
			if((pecas[i].ladoA + pecas[i].ladoB) > maior) {
				maior = pecas[i].ladoA + pecas[i].ladoB;
				indice = i;
			}
		}
	}
	
	//Caso nenhum duplo tenha sido encontrado
	if (maior == -1) {
		for (int i = 0; i < 14; i++) {
			if((pecas[i].ladoA + pecas[i].ladoB) > maior) {
				maior = pecas[i].ladoA + pecas[i].ladoB;
				indice = i;
			}
		}
	}
	
	//Coloca a pe�a escolhida na mesa
	mesa[0].ladoE = pecas[indice].ladoA;
	mesa[0].ladoD = pecas[indice].ladoB;
	mesa[0].status = 'J';
	mesaE = mesa[0].ladoE;	
	mesaD = mesa[0].ladoD;
	pecas[indice].status = 'M';
	qtMesa = 1;
	
	//Define quem foi o jogador que colocou a pe�a
	if (indice < 7) {
		jogadorAtual = 1;	
	}
	
	else {
		jogadorAtual = 2;
	}
	
	limparTela();
	printf("\n------------------------------------\n");
	printf("|O jogador %d fez o primeiro lance. |\n", jogadorAtual);
	printf("------------------------------------\n\n");
	system("pause");
	limparTela();
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
    if (fwrite(&maquina, sizeof(int), 1, fp) != 1) { printf("Erro na gravacao da maquina.\n"); fclose(fp); return; }

    fclose(fp);
    printf("\n----------JOGO SALVO COM SUCESSO!----------\n");
    Sleep(1000);
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
