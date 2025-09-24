//DOM-KLRR-MAIN.cpp - Projeto Dominó
//23/09/2025 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#include "DOM-KLRR-MODEL.cpp"
#include "DOM-KLRR-CONTROLLER.cpp"

//Função principal do programa
int main() {
	gerarPecas();				//Cria todas as 28 peças do dominó
	jogar();					//Inicia o fluxo do jogo (menu + lógica)
}
