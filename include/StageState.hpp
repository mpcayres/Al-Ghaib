/*
 * State.hpp
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

#include <vector>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "Sprite.hpp"
#include "Alien.hpp"
#include "TileSet.hpp"
#include "TileMap.hpp"
#include "State.hpp"
#include "Music.hpp"
#include "Timer.hpp"
#include "StateData.hpp"

#ifndef INCLUDE_STAGESTATE_HPP_
#define INCLUDE_STAGESTATE_HPP_

class StageState : public State{

private:
	Sprite bg;
	TileSet tileSet;
	TileMap tileMap;
	Timer time;
	bool flagMorte;

	Music music;

public:
	StageState();
	~StageState();

	void Pause();
	void Resume();

	void LoadAssets();

	void Update(float dt);
	void Render();

	StateData stateData;
};


#endif /* INCLUDE_STATE_HPP_ */
