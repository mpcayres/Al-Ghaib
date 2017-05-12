/*
 * Alien.hpp
 *
 *  Created on: 2 de abr de 2017
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <vector>

#include "GameObject.hpp"
#include "Minion.hpp"
#include "Camera.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"

#ifndef INCLUDE_ALINE_HPP_
#define INCLUDE_ALINE_HPP_

class Alien : public GameObject{
public:
	Alien(float x, float y, int nMinions);
	~Alien();
	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	static int alienCount;

private:
	enum AlienState{ MOVING, RESTING };

	AlienState state;
	Timer restTimer;
	Vec2 destination;
	Sprite sp;
	Vec2 speed;
	int hp;
	int actionDelay;


	std::vector<Minion> minionArray;
};


#endif /* INCLUDE_ALINE_HPP_ */












