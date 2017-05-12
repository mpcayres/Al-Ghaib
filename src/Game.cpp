/*
 * Game.cpp
 *
 *  Created on: 20 de mar de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */
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
		std::cout << "Instance already exists";
		exit(1);
	}

	//std::cout << "Instance created";
	instance = this;


	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER) != 0){
		printf("SDL_Init falhou: %s\n", SDL_GetError());
		exit(1);
	}

	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if((initted & flags) != flags) {
	    printf("IMG_Init: %s\n", IMG_GetError());
	    exit(1);
	}

	//flags = MIX_INIT_FLAC| MIX_INIT_MP3| MIX_INIT_OGG;//
	initted = Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
	if(initted == 0){
		std::cout << "Mix_Init falhou: " << Mix_GetError();
	}

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0){
		printf("Mix_OpenAudio falhou: %s\n", SDL_GetError());
		exit(1);
	}

	if(TTF_Init() != 0){
		printf("TTF_Init falhou: %s\n", SDL_GetError());
		exit(1);
	}

	const char * titulo = title.c_str();
	window = SDL_CreateWindow(titulo,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,0);
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(window == nullptr || renderer == nullptr){
		printf("Falha: %s\n", SDL_GetError());
		exit(1);
	}

//	std::cout << "\nWindow and Renderer created";

	srand(time(NULL));
	storedState = nullptr;
}

Game::~Game(){
	if(storedState != nullptr) delete(storedState);

	while(!stateStack.empty()){
		stateStack.pop();
	}

	IMG_Quit();
	Mix_CloseAudio();
	Mix_Quit();
	TTF_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Game::CalculateDeltaTime(){
	float a,b;
	a = (float)frameStart;
	frameStart = SDL_GetTicks();
	b = (float)frameStart;
	dt = (b-a)/1000;
}

float Game::GetDeltaTime(){
	return dt;
}

void Game::Push(State *state){ storedState = state;}

Game& Game::GetInstance(){return *instance;}

State& Game::GetCurrentState(){return *stateStack.top();}

SDL_Renderer* Game::GetRenderer(){return renderer;}

int Game::GetWidth(){
	return width;
}
int Game::GetHeight(){
	return height;
}

void Game::Run(){
	//std::cout << "\nJogo Rodando";
	if(storedState != nullptr){
		stateStack.emplace(storedState);
		storedState = nullptr;

		while(!stateStack.empty() && stateStack.top()->QuitRequested() == false){
			CalculateDeltaTime();
			stateStack.top()->Render();
			InputManager::GetInstace().Update();
			stateStack.top()->Update(dt);
			SDL_RenderPresent(renderer);

			if(stateStack.top()->PopRequested() == true){
				stateStack.pop();
				if(!stateStack.empty()){
					stateStack.top()->Resume();
				}

				Resources::ClearFont();
				Resources::ClearImages();
				Resources::ClearMusic();
				Resources::ClearSound();
			}
			if(storedState != nullptr){
				stateStack.top()->Pause();
				stateStack.emplace(storedState);
				storedState = nullptr;
			}
			SDL_Delay(33);

		}
	}
	Resources::ClearFont();
	Resources::ClearImages();
	Resources::ClearMusic();
	Resources::ClearSound();
}
