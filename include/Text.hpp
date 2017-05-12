#ifndef INCLUDE_FONT_HPP_
#define INCLUDE_FONT_HPP_

#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
	#include <SDL_ttf/SDL_ttf.h>
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_ttf.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"
#endif

#include <string>
#include <memory>

class Text{
public:
	enum TextStyle{SOLID, SHADED, BLENDED};

	Text();
	Text(std::string fontFile, int fontSize, TextStyle style, std::string text,
			SDL_Color color, int x = 0,int y = 0);
	~Text();
	void Render(int cameraX = 0, int cameraY = 0);
	void SetPos(int x, int y, bool centerX = false, bool centerY = false);

	void SetText(std::string text);
	void SetColor(SDL_Color color);
	void SetStyle(TextStyle style);
	void SetFontSize(int fontSize);

private:
	void RemakeTexture();

	std::shared_ptr<TTF_Font> font;
	SDL_Texture* texture;

	std::string text;
	TextStyle style;
	int fontSize;
	SDL_Color color;
	Rect box;

};

#endif /* INCLUDE_FONT_HPP_ */
