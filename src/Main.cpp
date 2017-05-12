/*
 * main.cpp
 *
 *  Created on: 18 de mar de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#include "Game.hpp"
#include "TitleState.hpp"
int main(int argc, char* argv[]) {
	Game game = Game("140030930 Renne Ruan Alves Oliveira",1024,600);
	game.Push(new TitleState());
	game.Run();

    return 0;
}
