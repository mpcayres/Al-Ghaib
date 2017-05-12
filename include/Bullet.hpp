/*
 * Bullet.hpp
 *
 *  Created on: 16 de abr de 2017
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

#include "GameObject.hpp"
#include "Sprite.hpp"

#ifndef INCLUDE_BULLET_HPP_
#define INCLUDE_BULLET_HPP_

class Bullet : public GameObject{
public:
	Bullet(float x, float y, float angle, float speed, float maxDistance,
			std::string sprite, int frame, float frameTime, bool isPlayer);
	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool targetsPlayer;
private:
	Sprite sp;
	Vec2 speed;
	float distanceLeft;
};



#endif /* INCLUDE_BULLET_HPP_ */
