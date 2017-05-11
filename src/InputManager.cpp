#include "InputManager.h"

InputManager::InputManager(){
	for(int i = 0; i < 6; i++){
		mouseState[i] = false;
		mouseUpdate[i] = 0;
	}

	quitRequested = false;
	updateCounter = 0;

	mouseX = 0;
	mouseY = 0;
}

InputManager::~InputManager(){ }

InputManager& InputManager::GetInstance(){
	static InputManager instance;
	return instance;
}

void InputManager::Update(){
	SDL_Event event;

	updateCounter++;
	//updateCounter = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	quitRequested = false;

	while(SDL_PollEvent(&event)) {
		//updateCounter em UP e se não coloca ao final do while
		switch(event.type){
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE)
					quitRequested = true;

				if(event.key.repeat != 1){
					keyState[event.key.keysym.sym] = true;
					keyUpdate[event.key.keysym.sym] = updateCounter;
					updateCounter++;
				}
				break;
			case SDL_KEYUP:
				if(event.key.repeat != 1){
					keyState[event.key.keysym.sym] = false;
					keyUpdate[event.key.keysym.sym] = updateCounter;
					updateCounter++;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
				updateCounter++;
				break;
			case SDL_MOUSEBUTTONUP:
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
				updateCounter++;
				break;
			case SDL_QUIT:
				quitRequested = true;
				break;
		}
	}
}

bool InputManager::KeyPress(int key){
	return keyState[key] && (keyUpdate[key]+1 == updateCounter);
}

bool InputManager::IsKeyDown(int key){
	return keyState[key];
}

bool InputManager::KeyRelease(int key){
	return ((!keyState[key]) && (keyUpdate[key]+1 == updateCounter));
}

bool InputManager::MousePress(int button){
	return mouseState[button] && (mouseUpdate[button]+1 == updateCounter);
}

bool InputManager::MouseRelease(int button){
	return ((!mouseState[button]) && (mouseUpdate[button]+1 == updateCounter));
}

bool InputManager::IsMouseDown(int button){
	return mouseState[button];
}

int InputManager::GetMouseX(){
	return mouseX;
}

int InputManager::GetMouseY(){
	return mouseY;
}

bool InputManager::QuitRequested(){
	return quitRequested;
}
