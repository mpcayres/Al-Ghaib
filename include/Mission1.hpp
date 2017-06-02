#ifndef MISSION1_HPP
#define MISSION1_HPP


#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
	#include <SDL_mixer/SDL_mixer.h>
	#include <SDL_ttf/SDL_ttf.h>
#elif __linux__
    #include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_ttf.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
#endif

#include "Mission.hpp"
#include "InputManager.hpp"
#include "Text.hpp"
#include "Timer.hpp"

class Mission1 : public Mission {
public:
	Mission1();
	~Mission1();

	void Pause();
	void Resume();

	void Update(float dt);
	void Render();
protected:
	void SetObjectStage();
	void SetObjectHall();

	Text tx;
	Timer time;
	bool flagTimer;
};

#endif /* SRC_MISSION1_HPP_ */