/*
 * Camera.hpp
 *
 *  Created on: 31 de mar de 2017
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

#include "GameObject.hpp"

#ifndef INCLUDE_CAMERA_HPP_
#define INCLUDE_CAMERA_HPP_


class Camera{
public:
	static void Follow(GameObject* newFocus);
	static void Unfollow();
	static void Update(float dt);

	static Vec2 pos;
	static Vec2 speed;

private:
	static GameObject* focus;
};

#endif
