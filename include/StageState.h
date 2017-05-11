#ifndef STAGE_STATE_H_
#define STAGE_STATE_H_

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
#include "TileSet.h"
#include "TileMap.h"
#include "State.h"
#include "Music.h"

class StageState : public State {
public:
	StageState();
	virtual ~StageState();

	void Update(float dt);
	void Render();

	void Pause();
	void Resume();

private:
	Sprite bg;
	TileSet *tileSet;
	TileMap *tileMap;
	Music *music;
};

#endif /* STATE_H_ */
