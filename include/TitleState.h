#ifndef TITLE_STATE_H_
#define TITLE_STATE_H_

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#elif __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#elif __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif

#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "Timer.h"

class TitleState : public State {
public:
	TitleState();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	Text text;

	Timer timer;
	bool textShow;
};

#endif /* TITLE_STATE_H_ */
