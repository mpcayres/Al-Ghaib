#include "TileMap.h"
#include <iostream>
#include <cstdio>

TileMap::TileMap(std::string file, TileSet* tileSet) : tileSet(tileSet) {
	Load(file);
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

void TileMap::SetTileSet(TileSet* tileSet){
	this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z){
	return ( (int&) tileMatrix.at(x + y*mapWidth + z*mapWidth*mapHeight) );
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

int TileMap::GetWidth(){
	return mapWidth;
}

int TileMap::GetHeight(){
	return mapHeight;
}

int TileMap::GetDepth(){
	return mapDepth;
}
