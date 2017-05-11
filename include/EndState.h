#ifndef END_STATE_H_
#define END_STATE_H_

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_mixer.h>
	#include <SDL_ttf.h>
#elif __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
	#include <SDL2_mixer/SDL_mixer.h>
	#include <SDL2_ttf/SDL_ttf.h>
#elif __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_ttf.h>
#endif

#include "Sprite.h"
#include "State.h"
#include "Text.h"
#include "Music.h"
#include "StateData.h"

class EndState : public State {
public:
	EndState(StateData stateData);

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	Music music;
	Text instruction;
};

#endif /* END_STATE_H_ */
