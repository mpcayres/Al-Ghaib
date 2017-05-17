#ifndef INCLUDE_TITLESTATE_HPP_
#define INCLUDE_TITLESTATE_HPP_

#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include "State.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Timer.hpp"
#include "MenuHUD.hpp"

class TitleState : public State {
public:
	TitleState();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();
private:
	Sprite bg;
	Text tx;
	Timer time;
	bool flagTimer;
	MenuHUD menu;

	enum { MENU_START, MENU_CONTINUE, MENU_OPTIONS };
};

#endif /* INCLUDE_TITLESTATE_HPP_ */
