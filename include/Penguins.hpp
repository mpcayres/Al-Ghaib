/*
 * Penguins.hpp
 *
 *  Created on: 5 de mai de 2017
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

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"


#ifndef INCLUDE_PENGUINS_HPP_
#define INCLUDE_PENGUINS_HPP_

class Penguins : public GameObject{
public:
	Penguins(float x, float y);
	~Penguins();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	void Shoot();
	bool Is(std::string type);

	static Penguins * player;


private:
	Timer time;
	Sprite bodySp;
	Sprite cannonSp;
	Vec2 speed;
	float linearSpeed;
	float cannonAngle;
	int hp;
	int deltaX, deltaY;

	Rect AuxCannon;

};




#endif /* INCLUDE_PENGUINS_HPP_ */
