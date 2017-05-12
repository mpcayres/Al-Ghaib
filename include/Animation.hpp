/*
 * Animation.hpp
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

#include "GameObject.hpp"
#include "Timer.hpp"
#include "Sprite.hpp"

#ifndef INCLUDE_ANIMATION_HPP_
#define INCLUDE_ANIMATION_HPP_

class Animation : public GameObject{
public:
	Animation(float x, float y, float rotation, std::string sprite, int frameCount,
			float frameTime, bool ends);
	void Update(float dt);
	void Render();
	bool IsDead();

	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	Timer endTimer;
	float timeLimit;
	bool oneTimeOnly;
	Sprite sp;
};



#endif /* INCLUDE_ANIMATION_HPP_ */
