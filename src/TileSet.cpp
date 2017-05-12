/*
 * TileSet.cpp
 *
 *  Created on: 22 de mar de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#include "TileSet.hpp"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file){
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	tileSet.Open(file);
	rows = (tileSet.GetHeight()/tileHeight);
	columns = (tileSet.GetWidth()/tileWidth);

	//std::cout << rows <<" "<< columns;
}

void TileSet::Render(unsigned index,float x, float y){
	int valoresClipx, valoresClipy;
	int auxLinhas, auxRestoLinhas;

	if (index < (unsigned)(rows*columns)-1){
		if(index >= (unsigned) columns){
			auxLinhas = index/columns;
			auxRestoLinhas = index % columns;

			valoresClipx = auxRestoLinhas * tileWidth;
			valoresClipy = auxLinhas * tileHeight;
		}else {
			valoresClipx = index * tileWidth;
			valoresClipy = 0;
		}
		tileSet.SetClip(valoresClipx, valoresClipy, tileWidth, tileHeight);
		tileSet.Render(x ,y, 0);
	}
}

int TileSet::GetTileHeight(){
	return tileHeight;
}

int TileSet::GetTileWidth(){
	return tileWidth;
}

