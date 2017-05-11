#ifndef TEXT_H_
#define TEXT_H_

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_ttf.h>
#elif __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_ttf/SDL_ttf.h>
#elif __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
#endif

#include <string>
#include <memory>
#include "Rect.h"

class Text {
public:
	enum TextStyle {SOLID, SHADED, BLENDED};

	Text(std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int x = 0, int y = 0);
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
	int fontSize;
	TextStyle style;
	std::string text;
	SDL_Color color;
	Rect box;
};

#endif /* TEXT_H_ */
