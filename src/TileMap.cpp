/*
 * TileMap.cpp
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
#include "TileMap.hpp"

TileMap::TileMap(std::string file, TileSet* tileSet){
	Load(file);
	this->tileSet = tileSet;
}

/*TODO conferir*/
void TileMap::Load(std::string file){
	FILE* arquivo;
	int aux;
	arquivo = fopen(file.c_str(), "r");
	if(arquivo != NULL){
		fscanf(arquivo, "%d", &mapWidth); fgetc(arquivo);
		fscanf(arquivo, "%d", &mapHeight); fgetc(arquivo);
		fscanf(arquivo, "%d", &mapDepth);
		while(!feof(arquivo)){
			fgetc(arquivo);
			fscanf(arquivo,"%d", &aux);
			aux--;
			tileMatrix.push_back(aux);
		//	std::cout <<tileMatrix[i] <<"\n";
		}
	}
}

void TileMap::RenderLayer(int Layer, int cameraX, int cameraY){
	float posx = cameraX, posy = cameraY;
	unsigned i, aux, tamanho_layer;
	int larguraTile = tileSet->GetTileWidth();

	aux = mapWidth*mapHeight * Layer;
	tamanho_layer = (unsigned) (mapWidth*mapHeight);

	for(i = 0; i< tamanho_layer; i++){
		if(tileMatrix[i+aux] >= 0)
			tileSet->Render((unsigned)tileMatrix[i+aux],posx,posy);
		posx = posx + larguraTile;
		if(posx - cameraX >= mapWidth*larguraTile){
			posx = cameraX;
			posy += tileSet->GetTileHeight();
		}
	}
}

void TileMap::Render(int cameraX, int cameraY){
	int i;

	for(i = 0; i < mapDepth; i++){
		if(i == 0)RenderLayer(i, cameraX, cameraY);
		else RenderLayer(i, cameraX*2, cameraY*2);
	}
}
void TileMap::SetTileSet(TileSet *tileSet){
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
	return tileMatrix[((y*mapWidth) + x) + (z*x*y)];
}

int TileMap::GetDepth(){
	return mapDepth;
}
int TileMap::GetHeight(){
	return mapHeight;
}
int TileMap::GetWidth(){
	return mapWidth;
}
