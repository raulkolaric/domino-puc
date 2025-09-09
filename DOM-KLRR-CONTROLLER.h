//DOM-KLRR-CONTROLLER.h - Projeto Dominó
//26/08/25 - Grupo: KLRR
//Kauã Bezerra Brito
//Liam Vedovato Lopes
//Raul Kolaric
//Rodrigo Ward Leite

#ifndef DOM_KLRR_CONTROLLER_H
#define DOM_KLRR_CONTROLLER_H

//Bibliotecas padrão
#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

//Declaração das funções utilizadas no jogo
void embaralhar();
void iniciarJogo();
void jogar();
void prepararJogo();
int primeiroLance();
void trocarJogador();
void jogarNaMesa();
void passar();
void salvarJogo();
void carregarJogo();

#endif // DOM_KLRR_CONTROLLER_H


