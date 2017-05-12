/*
 * GameObject.hpp
 *
 *  Created on: 20 de mar de 2017
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

#include "Geometry.hpp"

#ifndef INCLUDE_GAMEOBJECT_HPP_
#define INCLUDE_GAMEOBJECT_HPP_

class GameObject{

public:
	virtual ~GameObject(){};

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual bool IsDead() = 0;
	virtual void NotifyCollision(GameObject& other) = 0;
	virtual bool Is(std::string type) = 0;

	float rotation;
	Rect box;

};

#endif /* INCLUDE_GAMEOBJECT_HPP_ */
