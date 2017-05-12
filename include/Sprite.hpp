/*
 * Sprite.hpp
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
	#define SISTEMA 1
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#define SISTEMA 2
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
	#define SISTEMA 3
#else

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <memory>

#ifndef INCLUDE_SPRITE_HPP_
#define INCLUDE_SPRITE_HPP_

class Sprite{

private:
	std::shared_ptr<SDL_Texture> texture;
	int width, height;
	SDL_Rect clipRect;
	float scaleX;
	float scaleY;

	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;

public:
	Sprite();
	Sprite(std::string file, int frameCount = 1, float frameTime = 1);
	~Sprite();

	void SetScaleX(float scale);
	void SetScaleY(float scale);

	void Update(float dt);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);

	void Open(std::string file);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y, float angle);
	int GetWidth();
	int GetHeight();
	bool IsOpen();
};



#endif /* INCLUDE_SPRITE_HPP_ */
