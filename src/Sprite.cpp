#include "Sprite.h"
#include "Game.h"
#include "Resources.h"
#include <iostream>
#include <stdlib.h>

Sprite::Sprite() {
	texture = nullptr;
	width = height = 0;
	scaleX = scaleY = 1;
	frameCount = frameTime = 1;
	timeElapsed = 0; currentFrame = 0;
}

Sprite::Sprite(std::string file, int frameCount, float frameTime) :
	frameCount(frameCount), frameTime(frameTime) {
	texture = nullptr;
	scaleX = scaleY = 1;
	timeElapsed = currentFrame = 0;
	Sprite::Open(file, frameCount, frameTime);
}

Sprite::~Sprite() { }

void Sprite::Open(std::string file, int frameCount, float frameTime){
	texture = Resources::GetImage(file.c_str());

	if(SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height) != 0){
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}

	SetFrameCount(frameCount);
	SetFrameTime(frameTime);
	SetFrame(0);
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y, float angle){
	SDL_Rect dst;
	dst.x = x; dst.y = y;
	dst.w = clipRect.w*scaleX; dst.h = clipRect.h*scaleY;
	if(SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(),
			&clipRect, &dst, angle, NULL, SDL_FLIP_NONE) != 0){
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}
}

void Sprite::Update(float dt){
	if(frameCount != 1){
		timeElapsed += dt;
		if(timeElapsed > frameTime) {
			timeElapsed -= frameTime;
			SetFrame((currentFrame+1) % frameCount);
		}
	}
}

void Sprite::SetFrame(int frame){
	this->currentFrame = frame;
	SetClip(frame*GetWidth(), 0, GetWidth(), GetHeight());
}

void Sprite::SetFrameCount(int frameCount){
	this->frameCount = frameCount;
}

void Sprite::SetFrameTime(int frameTime){
	this->frameTime = frameTime;
}

int Sprite::GetWidth(){
	return (width*scaleX)/frameCount;
}

int Sprite::GetHeight(){
	return height*scaleY;
}

bool Sprite::IsOpen(){
	return (texture != nullptr);
}

void Sprite::SetScaleX(float scale){
	scaleX = scale;
}

void Sprite::SetScaleY(float scale){
	scaleY = scale;
}
