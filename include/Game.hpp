
/*
 * Game.hpp
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
	#include <SDL_mixer/SDL_mixer.h>
	#include <SDL_ttf/SDL_ttf.h>
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_ttf.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
#else

#endif

#include <deque>
#include <stack>
#include <StageState.hpp>
#include <iostream>
#include <memory>
#include <ctime>


#ifndef GAME_H
#define GAME_H

class Game{

private:
	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* storedState;

	std::stack<std::unique_ptr<State>>  stateStack;

	int frameStart;
	float dt;

	int width; int height;
	void CalculateDeltaTime();

public:
	Game(std::string title, int width, int height);
	Game(Game&&) = default;
    Game& operator=(Game&&) = default;
	~Game();

	void Run();
	SDL_Renderer* GetRenderer();
	State& GetCurrentState();
	static Game& GetInstance();

	void Push(State* state);

	float GetDeltaTime();

	int GetWidth();
	int GetHeight();
};


#endif


















