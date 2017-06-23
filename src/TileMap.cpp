#include <iostream>

#include "TileMap.hpp"
#include "MissionManager.hpp"

TileMap::TileMap(std::string file, TileSet* tileSet){
	this->tileSet = tileSet;
	Load(file);
}

void TileMap::Load(std::string file){
	FILE* fp = fopen(file.c_str(), "r");
	if(fp == nullptr){
		std::cout << "Erro ao abrir o arquivo: " << file << std::endl;
		exit(1);
	}

	fscanf(fp, "%d,%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth, &mapInsideSquares);

	int num;
	int x,y,c,a;
	int wiAux = tileSet->GetTileWidth();
	int heAux = tileSet->GetTileHeight();
	for(int i = 0; i < mapInsideSquares; i++){
		fscanf(fp, "%d,%d,%d,%d,", &x,&y,&c,&a);
		limitsVector.push_back(Rect((x * wiAux), (y*heAux), (c*wiAux), (a*heAux)));
	}

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
	int lastX = 0, lastY = 0 , firstX = 10000000, firstY = 10000000;
	int i;
	int value;

	for(i = 0; i< (mapHeight*mapWidth)-1 ; i++){
		if(tileMatrix[i] == 0){
			value = (i%mapWidth) * tileSet->GetTileWidth();
			if(value < firstX) firstX = value;
			if(value > lastX) lastX = value;

			if(i>mapWidth) value = (i/mapWidth)* tileSet->GetTileHeight();
			else value = 0;
			if(value < firstY) firstY = value;
			if(value > lastY) lastY = value;
		}
	}
	lastX += tileSet->GetTileWidth();
	lastY += tileSet->GetTileHeight();

	aux.x = firstX;
	aux.y = firstY;//firstY - MissionManager::player->box.h/2;//tileSet->GetTileHeight();
	aux.w = lastX; //lastX
	aux.h = lastY; //lastY

	return aux;
}

std::vector<Rect> TileMap::GetInnerLimits(){
	return limitsVector;
}
