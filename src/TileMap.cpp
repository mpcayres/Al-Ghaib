#include <iostream>

#include "TileMap.hpp"

TileMap::TileMap(std::string file, TileSet* tileSet){
	Load(file);
	this->tileSet = tileSet;
}

void TileMap::Load(std::string file){
	FILE* fp = fopen(file.c_str(), "r");
	if(fp == nullptr){
		std::cout << "Erro ao abrir o arquivo: " << file << std::endl;
		exit(1);
	}

	fscanf(fp, "%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth);
	int num;
	while(!feof(fp)){
		fscanf(fp, " %d,", &num);
		tileMatrix.push_back(num - 1);
	}

	fclose(fp);
}

void TileMap::Render(int cameraX, int cameraY){
	for(int i = 1; i < mapDepth; i++){
		TileMap::RenderLayer(i, cameraX, cameraY);
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
	for(int i = 0; i < mapWidth; i++){
		for(int j = 0; j < mapHeight; j++){
			int index = At(i, j, layer);
			if(index >= 0){
				int posX = DetermParallax(i*tileSet->GetTileWidth(), cameraX, layer);
				int posY = DetermParallax(j*tileSet->GetTileHeight(), cameraY, layer);
				tileSet->Render(index, posX, posY);
			}
		}
	}
}

int TileMap::DetermParallax(int pos, int camera, int layer){
	return (pos - camera*(layer+1));
}

void TileMap::SetTileSet(TileSet *tileSet){
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
	return ( (int&) tileMatrix.at(x + y*mapWidth + z*mapWidth*mapHeight) );
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

Rect TileMap::FindLimits(){
	Rect aux;
	int lastX, lastY, firstX, firstY;
	int i;
	int first = -1, last;

	for(i = 0; i< (mapHeight*mapWidth)-1 ; i++){
		if(tileMatrix[i] >= 0){
			if(first == -1) first = i;
			last = i;
		}
	}

	firstX = (first%mapWidth) * tileSet->GetTileWidth();
	if(first > mapWidth){
		firstY = (first/mapWidth)* tileSet->GetTileHeight();
	}else firstY = 0;

	lastX = (last%mapWidth) * tileSet->GetTileWidth();
	if(last > mapWidth){
		lastY = (last/mapWidth)* tileSet->GetTileHeight();
	}else lastY = 0;

	lastX += 2*tileSet->GetTileWidth();
	lastY += tileSet->GetTileHeight();

	aux.x = firstX;
	aux.y = firstY;
	aux.w = lastX;
	aux.h = lastY;

	return aux;
}

