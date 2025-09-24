//DOM-KLRR-VIEW.cpp - Projeto Dominó
//23/09/2025 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include "DOM-KLRR-VIEW.h"

//Mostra a mesa atual (apenas peças já jogadas)
void apresentarMesa() {
   //Calcula o tamanho do array 'mesa'
    int tamanho = sizeof(mesa) / sizeof(mesa[0]);
    
    printf("\n                                                     MESA                                          \n");
	printf("=======================================================================================================================\n");
	
    //Imprime todas as peças do array
    for (int i = 0; i < tamanho; i++) {
        if (mesa[i].status == 'J') {
			printf("[%d|%d] ", mesa[i].ladoE, mesa[i].ladoD);	
		}
    }
    
	printf("\n=======================================================================================================================\n");
}	

//Limpa o buffer de entrada
void fclear() {
	char carac;

	while ((carac = fgetc(stdin)) != EOF && carac != '\n') {
	
	}
}

//Limpa a tela do console
void limparTela() {
	system("cls");
}

//Variaveis para os Menus
char op1, op2;

//Exibe o menu principal e retorna a opção escolhida
char menuInicial() {
	do {
		limparTela();
				
		printf("\n-------------------MENU-------------------\n");
		printf("| 1 - Iniciar jogo (2 jogadores)         |\n");
		printf("| 2 - Iniciar jogo (contra o computador) |\n");
		printf("| 3 - Retornar ao jogo interrompido      |\n");
		printf("| 4 - Regras gerais do Jogo              |\n");
		printf("| 5 - Salvar o jogo                      |\n");
		printf("| 6 - Recuperar o jogo salvo             |\n");
		printf("| 0 - Sair do programa                   |\n");
		printf("------------------------------------------\n");
		printf("Opcao selecionada: ");
		scanf("%c", &op1);	
		
		if (op1 >= '0' && op1 <= '6')
			break;
			
		printf("\n--------------OPCAO INVALIDA--------------");	
		Sleep(500);
		fclear();
	} while (1);

	fclear();
	return op1; 
}

//Exibe o menu de jogadas dentro da partida
char menuJogador() {
	do {
		limparTela();
		apresentarMesa();
		mostrarPecas();
		
		printf("\n----------------------------------------------------------\n");
		printf("| J - Jogar (possiveis %d ou %d)                           |\n", mesaE, mesaD);
		printf("| C - Comprar                                            |\n");
		printf("| P - Passar                                             |\n");
		printf("| S - Sair (interromper o jogo voltando ao menu inicial) |\n");
		printf("----------------------------------------------------------\n");
		printf("Opcao selecionada: ");
		scanf(" %c", &op2);
		op2 = toupper(op2);
		
		if ((op2 == 'J') || (op2 == 'C') || (op2 == 'P') || (op2 == 'S')) {
			break;
		}
		
		printf("\n--------------OPCAO INVALIDA--------------");
		Sleep(500);
		fclear();	
	} while (1);

	fclear();
	return op2;
}

//Exibe as regras resumidas do dominó
void regras() {
	printf("\n-------------------------------------------------Regras-resumidas-do-Domino-------------------------------------------------\n");
	printf("1 - Distribuicao inicial: Cada jogador comeca com 7 pecas. As demais ficam no monte para compra.\n");
	printf("2 - Inicio do jogo: Comeca quem tiver o [6|6]. Se ninguem tiver, vale a peca de numero duplo mais alto (ex: [5|5], [4|4]...).\n");
	printf("3 - Sentido do jogo: O jogo segue em sentido anti-horario.\n");
	printf("4 - Como jogar:\n");
	printf("    O jogador deve colocar uma peca que combine com uma das extremidades da mesa.\n");
	printf("    Se nao tiver peca compativel, deve comprar do monte ate conseguir jogar.\n");
	printf("    Se o monte acabar e nao for possivel jogar, o jogador passa a vez.\n");
	printf("5 - Final do turno: Assim que o jogador coloca sua peca, a vez passa ao proximo.\n");
	printf("6 - Fim da partida:\n");
	printf("    Se alguem colocar sua ultima peça, vence automaticamente (bater).\n");
	printf("    Se o jogo travar (ninguem pode jogar e nao ha peças no monte), vence quem tiver menos pecas.\n");
	printf("    Em caso de empate, vence quem tiver a menor soma dos pontos nas pecas restantes.\n\n");
	system("pause");
}
