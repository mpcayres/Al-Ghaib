#include "Text.h"
#include "Game.h"
#include "Resources.h"
#include <iostream>

Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x, int y) : 
	fontSize(fontSize), style(style), text(text), color(color) {
	texture = nullptr;
	box.x = x; box.y = y;
	font = Resources::GetFont(fontFile, fontSize);
	RemakeTexture();
}

Text::~Text(){
	if(texture != nullptr){
		SDL_DestroyTexture(texture);
	}
}

void Text::Render(int cameraX, int cameraY){
	SDL_Rect src, dst;
	src.x = 0; src.y = 0;
	dst.x = box.x - cameraX; dst.y = box.y - cameraY;
	dst.w = src.w = box.w; dst.h = src.h = box.h;
	if(SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &src, &dst) != 0){
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}
}

void Text::SetPos(int x, int y, bool centerX, bool centerY){
	box.x = x; box.y = y;
	if(centerX){
		box.x -= box.w/2;
	}
	if(centerY){
		box.y -= box.h/2;
	}
	RemakeTexture();
}

void Text::SetText(std::string text){
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color){
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style){
	this->style = style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize){
	this->fontSize = fontSize;
	RemakeTexture();
}

void Text::RemakeTexture(){
	if(texture != nullptr){
		SDL_DestroyTexture(texture);
	}

	SDL_Surface* surface;

	if(style == SOLID){
		surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
	}

	if(style == SHADED){
		surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, { 0, 0, 0, 0 });
	}

	if(style == BLENDED){
		surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
	}

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	
	box.w = surface->w; box.h = surface->h;
	SDL_FreeSurface(surface);
}