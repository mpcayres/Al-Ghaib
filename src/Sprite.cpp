#include <iostream>

#include "Sprite.hpp"
#include "Game.hpp"
#include "Resources.hpp"

Sprite::Sprite(){
	texture = nullptr;
	height = 0; width = 0;
	scaleX = 1; scaleY = 1;
	frameCount = 1; frameTime = 1;
	timeElapsed = 0; currentFrame = 1;
}

Sprite::Sprite(std::string file, int frameCount, float frameTime){
	scaleX = 1; scaleY = 1;
	texture = nullptr;
	timeElapsed = 0; currentFrame = 1;
	Open(file, frameCount, frameTime);
}

Sprite::~Sprite(){}

void Sprite::Open(std::string file, int frameCount, float frameTime){
	this->frameCount = frameCount; this->frameTime = frameTime;
	texture = Resources::GetImage(file);

	SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height);
	SetClip(0, 0, GetWidth(), height);
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect.x = x; clipRect.y = y;
	clipRect.h = h; clipRect.w = w;
}

bool Sprite::IsOpen(){
	return (texture != nullptr);
}

void Sprite::Render(int x, int y, float angle){
	SDL_Rect dst;
	dst.x = x, dst.y = y;
	dst.h = clipRect.h*scaleY; dst.w = clipRect.w*scaleX;
	SDL_RenderCopyEx(Game::GetInstance().GetRenderer(), texture.get(),
			&clipRect, &dst, angle, nullptr, SDL_FLIP_NONE);
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
