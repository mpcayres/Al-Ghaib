#include <iostream>
#include <ctime>

#include "Game.hpp"
#include "Resources.hpp"
#include "InputManager.hpp"

Game* Game::instance;

Game::Game(std::string title, int width, int height){
	frameStart = 0;
	dt = 0;
	this->width = width;
	this->height = height;

	if(instance != nullptr){
		std::cout << "Instance already exists" << std::endl;
		exit(1);
	}

	instance = this;

	/* SDL_INIT_JOYSTICK | SDL_INIT_HAPTC | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS | SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE */
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0 ){
		std::cout << "SDL_Init falhou: " << SDL_GetError() << std::endl;
		exit(1);
	}

	int flagsIMG = (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	int initIMG = IMG_Init(flagsIMG);
	if((initIMG & flagsIMG) != flagsIMG) {
		std::cout << "IMG_Init: " << SDL_GetError() << std::endl;
		exit(1);
	}

	/* MIX_INIT_FLAC | MIX_INIT_MOD */
	int flagsMIX = (/*MIX_INIT_MP3 |*/ MIX_INIT_OGG);
	int initMIX = Mix_Init(flagsMIX);
	if((initMIX & flagsMIX) != flagsMIX) {
		std::cout << "Mix_Init falhou: " << SDL_GetError() << std::endl;
		exit(1);
	}

	if( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0 ){
		std::cout << "Mix_OpenAudio falhou: " << SDL_GetError() << std::endl;
		exit(1);
	}

	if( TTF_Init() != 0 ){
		std::cout << "TTF_Init falhou: " << SDL_GetError() << std::endl;
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

	srand(time(NULL));
	storedState = nullptr;
	missionManager = new MissionManager();
}

Game::~Game(){
	if(storedState != nullptr) delete (storedState);
	while(!stateStack.empty()) stateStack.pop();
	Resources::ClearResources();

	if(missionManager != nullptr) delete (missionManager);

	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::Run(){
	if(storedState != nullptr){
		stateStack.push(std::unique_ptr<State>(storedState));
		storedState = nullptr;

		while(!stateStack.empty() && GetCurrentState().QuitRequested() == false){
			CalculateDeltaTime();
			InputManager::GetInstance().Update();
			GetCurrentState().Update(dt);
			GetCurrentState().Render();
			SDL_RenderPresent(renderer);

			if(GetCurrentState().PopRequested()){
				//std::cout << "1: " << typeid(GetCurrentState()).name() << std::endl;
				GetCurrentState().Pause();
				stateStack.pop();
				Resources::ClearResources();
				if(!stateStack.empty())
					GetCurrentState().Resume();
				//std::cout << "2: " << typeid(GetCurrentState()).name() << std::endl;
			}
			if(storedState != nullptr){
				//std::cout << "3: " << typeid(GetCurrentState()).name() << std::endl;
				if(!stateStack.empty())
					GetCurrentState().Pause();
				stateStack.push(std::unique_ptr<State>(storedState));
				GetCurrentState().Resume();
				storedState = nullptr;
				//std::cout << "4: " << typeid(GetCurrentState()).name() << std::endl;
			}
			SDL_Delay(33);
		}
	}
}

void Game::CalculateDeltaTime(){
	Uint32 newFrame = SDL_GetTicks();
	dt = 0.001*((float) newFrame - frameStart);
	frameStart = newFrame;
}

float Game::GetDeltaTime(){
	return dt;
}

void Game::Push(State *state){
	storedState = state;
}

Game& Game::GetInstance(){
	return *instance;
}

State& Game::GetCurrentState(){
	return *stateStack.top();
}

MissionManager& Game::GetMissionManager(){
	return *missionManager;
}

SDL_Renderer* Game::GetRenderer(){
	return renderer;
}

int Game::GetWidth(){
	return width;
}

int Game::GetHeight(){
	return height;
}
