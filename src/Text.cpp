#include "Game.hpp"
#include "Text.hpp"
#include "Resources.hpp"

Text::Text(std::string fontFile, int fontSize, TextStyle style, std::string text,
		SDL_Color color, int x,int y){
	texture = nullptr;

	font = Resources::GetFont(fontFile, fontSize);

	this->fontSize = fontSize;
	this->style = style;
	this->text = text;
	this->color = color;

	box.x = x;
	box.y = y;

	if(font != nullptr){
		RemakeTexture();
	}
}

Text::Text(){
	SDL_Color auxcolor = SDL_Color();
	auxcolor.r = 0;
	auxcolor.g = 0;
	auxcolor.b = 0;
	fontSize = 0;
	style = SOLID;
	text = "";
	color = auxcolor;
	font = nullptr;
	texture = nullptr;
	box.x = 0;
	box.y = 0;
}

Text::~Text(){
	if(texture != nullptr) texture = nullptr;
}

void Text::Render(int cameraX, int cameraY){
	SDL_Rect src, dst;
	src.x = 0; src.y = 0;
	src.w = box.w; src.h = box.h;
	dst.x = box.x + cameraX, dst.y = box.y + cameraY;
	dst.h = box.h; dst.w = box.w;

	if(texture != nullptr){
		SDL_RenderCopy(Game::GetInstance().GetRenderer(), texture, &src, &dst);
	}

}


void Text::SetPos(int x, int y, bool centerX, bool centerY){
	if(centerX == false){
		box.x = x;
	} else{
		box.x = Game::GetInstance().GetWidth()/2 - box.w/2;
	}
	if(centerY == false){
		box.y = y;
	} else{
		box.y = Game::GetInstance().GetHeight()/2 - box.h/2;
	}
}

void Text::SetColor(SDL_Color color){
	this->color = color;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize){
	this->fontSize = fontSize;
	RemakeTexture();
}

void Text::SetStyle(enum TextStyle style){
	this->style = style;
	RemakeTexture();
}

void Text::SetText(std::string text){
	this->text = text;
	RemakeTexture();
}

void Text::RemakeTexture(){
	SDL_Color fundo = SDL_Color();
	fundo.b = fundo.g, fundo.r = 0;
	SDL_Surface* aux;

	if(texture != nullptr) texture = nullptr;

	if(style == SOLID){
		aux = TTF_RenderText_Solid(font.get(),text.c_str(), color);
	} else if(style == SHADED){
		aux = TTF_RenderText_Shaded(font.get(),text.c_str(), color, fundo);
	} else{
		aux = TTF_RenderText_Blended(font.get(),text.c_str(), color);
	}

	box.w = aux->w;
	box.h = aux->h;

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(),aux);
	if(texture == NULL){
		printf("SDL_CreateTextureFromSurface falhou: %s\n", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(aux);

}
