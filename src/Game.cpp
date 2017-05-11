#include "Game.h"
#include "Resources.h"
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>

Game* Game::instance = nullptr;

Game::Game(std::string title, int width, int height) :
		frameStart(SDL_GetTicks()), dt(0.0) {
	if(instance == nullptr) instance = this;

	srand(time(NULL));

	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0){
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}

	if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)
			!= (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)){
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}

	if(Mix_Init( MIX_INIT_OGG | MIX_INIT_MP3 ) <= 0){
        std::cout << SDL_GetError() << std::endl;
		exit(1);
    }

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}

	if(TTF_Init() != 0) {
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, 0);
	if(window == nullptr){
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if(renderer == nullptr){
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}

	storedState = nullptr;
}

Game::~Game() {
	while(!stateStack.empty()){
		stateStack.pop();
	}
	if(storedState != nullptr) delete(storedState);
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Run(){
	if(storedState != nullptr){
		stateStack.push(std::unique_ptr<State>(storedState));
		storedState = nullptr;
	} else return;

	// Conferir esses resumes e pauses
	while(!stateStack.empty()){
		if(GetCurrentState().QuitRequested()) break;
		CalculateDeltaTime();
		InputManager::GetInstance().Update();
		GetCurrentState().Update(dt);
		GetCurrentState().Render();
		SDL_RenderPresent(renderer);
		if(GetCurrentState().PopRequested()){
			GetCurrentState().Pause();
			stateStack.pop();
			Resources::ClearResources();
			if(!stateStack.empty())
				GetCurrentState().Resume();
		}
		if(storedState != nullptr){
			if(!stateStack.empty())
				GetCurrentState().Pause();
			stateStack.push(std::unique_ptr<State>(storedState));
			GetCurrentState().Resume();
			storedState = nullptr;
		}
		SDL_Delay(33);
	}

	Resources::ClearResources();
}

SDL_Renderer* Game::GetRenderer(){
	return renderer;
}

State& Game::GetCurrentState(){
	return *stateStack.top();
}

Game& Game::GetInstance(){
	return *instance;
}

void Game::Push(State* state){
	if(storedState != nullptr) delete storedState;
	storedState = state;
}

float Game::GetDeltaTime(){
	return dt;
}

void Game::CalculateDeltaTime(){
	Uint32 newFrame = SDL_GetTicks();
	dt = 0.001*((float) newFrame - frameStart);
	frameStart = newFrame;
}
