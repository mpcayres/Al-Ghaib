/*
 * Timer.hpp
 *
 *  Created on: 9 de mai de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
#else

#endif

#ifndef INCLUDE_TIMER_HPP_
#define INCLUDE_TIMER_HPP_

class Timer{
public:
	Timer();
	void Update(float dt);
	void Restart();
	float Get();

private:
	float time;
};

#endif /* INCLUDE_TIMER_HPP_ */
