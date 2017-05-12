/*
 * Minion.hpp
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

#include "Sprite.hpp"
#include "GameObject.hpp"

#ifndef INCLUDE_MINION_HPP_
#define INCLUDE_MINION_HPP_

class Minion : public GameObject{
public:
	Minion(GameObject* minionCenter, float arcOffset = 0);
	void Update(float dt);
	void Render();
	bool IsDead();
	void Shoot(Vec2 pos);
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	GameObject* center;
	bool dead;
	Sprite sp;
	float arc;
};



#endif /* INCLUDE_MINION_HPP_ */
