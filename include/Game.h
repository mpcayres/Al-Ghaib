#ifndef GAME_H_
#define GAME_H_

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

#include <string>
#include <stack>
#include <memory>
#include "Camera.h"
#include "State.h"
#include "InputManager.h"

class Game {
public:
	Game(std::string title, int width, int height);
	Game(Game&&) = default;
    Game& operator=(Game&&) = default;
	~Game();

	void Run();

	SDL_Renderer* GetRenderer();
	State& GetCurrentState();
	static Game& GetInstance();

	void Push(State* state);
	float GetDeltaTime();

private:
	void CalculateDeltaTime();

	static Game* instance;
	SDL_Window* window;
	SDL_Renderer* renderer;
	State* storedState;
	std::stack<std::unique_ptr<State>> stateStack;

	int frameStart;
	float dt;
};

#endif /* GAME_H_ */
