/*
 * TileMap.hpp
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
#include <vector>

#ifndef INCLUDE_TILEMAP_HPP_
#define INCLUDE_TILEMAP_HPP_

#include "TileSet.hpp"

class TileMap{
public:
	TileMap(std::string file, TileSet* tileSet);
	void Load(std::string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z=0);
	void Render(int cameraX, int cameraY);
	void RenderLayer(int layer, int cameraX, int cameraY);
	int GetWidth();
	int GetHeight();
	int GetDepth();

private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};


#endif /* INCLUDE_TILEMAP_HPP_ */
