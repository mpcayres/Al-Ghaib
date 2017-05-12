/*
 * TileSet.hpp
 *
 *  Created on: 22 de mar de 2017
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

#ifndef INCLUDE_TILESET_HPP_
#define INCLUDE_TILESET_HPP_

#include "Sprite.hpp"

class TileSet{
public:
	TileSet(int tileWidth, int tileHeight, std::string file);
	void Render(unsigned index, float x, float y);
	int GetTileWidth();
	int GetTileHeight();

private:
	Sprite tileSet;
	int rows;
	int columns;

	int tileWidth;
	int tileHeight;
};

#endif /* INCLUDE_TILESET_HPP_ */
