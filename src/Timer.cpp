/*
 * Timer.cpp
 *
 *  Created on: 9 de mai de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */
#include "Timer.hpp"

Timer::Timer(){time = 0;}

void Timer::Update(float dt){time += dt;}

void Timer::Restart(){ time = 0;}

float Timer::Get(){return time;}



