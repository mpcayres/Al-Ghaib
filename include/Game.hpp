#ifndef GAME_HPP
#define GAME_HPP

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

#include <string>
#include <stack>
#include <memory>

#include "State.hpp"
#include "MissionManager.hpp"
#include "Mission.hpp"

#define SCREEN_SIZE_W 1024
#define SCREEN_SIZE_H 600

class Game{
public:
	Game(std::string title, int width, int height);
	Game(Game&&) = default;
    Game& operator=(Game&&) = default;
	~Game();

	void Run();
	SDL_Renderer* GetRenderer();
	State& GetCurrentState();
	MissionManager& GetMissionManager();
	static Game& GetInstance();

	void Push(State* state);
	void Push(Mission* mission);

	Mission* storedMission;

	float GetDeltaTime();

	int GetWidth();
	int GetHeight();

private:
	void CalculateDeltaTime();

	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* storedState;
	MissionManager* missionManager;

	std::stack<std::unique_ptr<State>> stateStack;

	int frameStart;
	float dt;

	int width; int height;

};


#endif
