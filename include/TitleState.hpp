#ifndef INCLUDE_TITLESTATE_HPP_
#define INCLUDE_TITLESTATE_HPP_

#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
	#include <SDL_mixer/SDL_mixer.h>
#elif __linux__
    #include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
#endif

#include "State.hpp"
#include "Sprite.hpp"
#include "Text.hpp"
#include "Timer.hpp"
#include "MenuHUD.hpp"
#include "Music.hpp"

class TitleState : public State {
public:
	TitleState();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	static void LinkMusic();

	Sprite bg, control;
	//Text tx;
	Timer time;
	static Music intro, music;
	bool flagTimer, controlPop, shift;
	static bool stopMusic;
	MenuHUD menu;

	enum { MENU_START, MENU_CONTINUE, MENU_OPTIONS, MENU_EXIT };
};

#endif /* INCLUDE_TITLESTATE_HPP_ */
