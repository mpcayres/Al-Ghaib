/*
 * State.hpp
 *
 *  Created on: 10 de mai de 2017
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
#include <iostream>
#include <memory>
#include <vector>

#ifndef INCLUDE_STATE_HPP_
#define INCLUDE_STATE_HPP_

class State{

protected:
	virtual void UpdateArray(float dt);
	virtual void RenderArray();

	bool quitRequested;
	bool popRequested;

	std::vector<std::unique_ptr<GameObject>> objectArray;

public:
	State();
	virtual ~State();

	virtual void AddObject(GameObject *object);

	bool PopRequested();
	bool QuitRequested();

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
};



#endif /* INCLUDE_STATE_HPP_ */
