/*
 * InputManager.hpp
 *
 *  Created on: 24 de mar de 2017
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
#include <unordered_map>


#ifndef INCLUDE_INPUTMANAGER_HPP_
#define INCLUDE_INPUTMANAGER_HPP_

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACE_KEY SDLK_SPACE
#define W_KEY SDLK_w
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define D_KEY SDLK_d

class InputManager{
public:
	InputManager();
	~InputManager();

	void Update();

	bool KeyPress(int key);
	bool KeyRelease(int key);
	bool IsKeyDown(int key);

	bool MousePress(int button);
	bool MouseRelease(int button);
	bool IsMouseDown(int button);

	int GetMouseX();
	int GetMouseY();

	bool QuitRequested();

	static InputManager& GetInstace();

private:
	bool mouseState[6];
	int mouseUpdate[6];

	std::unordered_map<int, bool> keyState;
	std::unordered_map<int, int> keyUpdate;

	bool quitRequested;
	int updateCounter;

	int mouseX;
	int mouseY;
};



#endif /* INCLUDE_INPUTMANAGER_HPP_ */










