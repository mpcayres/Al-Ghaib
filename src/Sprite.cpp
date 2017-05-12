/*
 * Sprite.cpp
 *
 *  Created on: 18 de mar de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */
#include "Sprite.hpp"
#include "Game.hpp"
#include "Resources.hpp"

#define PATHWINDOWS 3
#define PATHLINUX 2

//SDL_Texture* Resources::GetImage(std::string file);

Sprite::Sprite(){
	texture = nullptr;
	height = 0; width = 0;
	scaleX = 1; scaleY = 1;
	frameCount = 1; frameTime = 1;
	timeElapsed = 0; currentFrame = 1;
}

Sprite::Sprite(std::string file, int frameCount, float frameTime){
	this->frameCount = frameCount; this->frameTime = frameTime;
	scaleX = 1; scaleY = 1;
	texture = nullptr;
	timeElapsed = 0; currentFrame = 1;
	Open(file);
}

Sprite::~Sprite(){
}

void Sprite::Open(std::string file){
	texture = Resources::GetImage(file);
	if(texture == nullptr){
		printf("LoadTexture falhou: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_QueryTexture(texture.get(),nullptr,nullptr,&width,&height);
	SetClip(0,0,GetWidth(),height);
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect.x = x; clipRect.y = y;
	clipRect.h = h; clipRect.w = w;
}

bool Sprite::IsOpen(){
	if(texture == nullptr) return false;
	else return true;
}

void Sprite::Render(int x, int y, float angle){
	SDL_Rect dst;
	dst.x = x, dst.y = y;
	dst.h = clipRect.h*scaleY; dst.w = clipRect.w*scaleX;
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(),texture.get(),&clipRect,&dst,angle,nullptr, SDL_FLIP_NONE);
}

void Sprite::SetScaleX(float scale){
	scaleX = scale;
}
void Sprite::SetScaleY(float scale){
	scaleY = scale;
}

void Sprite::Update(float dt){
	timeElapsed += dt;

	if (timeElapsed >= frameTime){
		timeElapsed -= frameTime;
		currentFrame++;
		if(currentFrame > frameCount) currentFrame = 1;
		SetFrame(currentFrame);
	}
}

void Sprite::SetFrame(int frame){
	currentFrame = frame;
	SetClip((frame-1)*GetWidth(), 0, GetWidth(),GetHeight());
}

void Sprite::SetFrameCount(int frameCountA){
	this->frameCount = frameCountA;
}

void Sprite::SetFrameTime(float frameTimeA){
	this->frameTime = frameTimeA;
}

int Sprite::GetWidth(){
	return (width * scaleX)/frameCount;
}
int Sprite::GetHeight(){
	return height * scaleY;
}
