/*
 * InputManager.cpp
 *
 *  Created on: 24 de mar de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */


#include "InputManager.hpp"

InputManager& InputManager::GetInstace(){
	static InputManager inputInstance;
	return inputInstance;
}

InputManager::InputManager(){
	int i;
	for(i = 0; i < 6; i++){
		mouseState[i] = false;
		mouseUpdate[i] = false;
	}

	quitRequested = false;
	updateCounter = 0;

	mouseX = mouseY = 0;
}

InputManager::~InputManager(){

}

void InputManager::Update(){
	SDL_Event event;

	updateCounter = 0;
	quitRequested = false;
	SDL_GetMouseState(&mouseX, &mouseY);

	 while (SDL_PollEvent(&event)) {
		 if(!event.key.repeat){
			 if(event.type == SDL_QUIT) {
				 quitRequested = true;
			 }
			 if(event.type == SDL_KEYDOWN) {
				 if(!event.key.repeat){
					 keyState[event.key.keysym.sym] = true;
				 	 keyUpdate[event.key.keysym.sym] = 1;
				 	 updateCounter++;
				 }
			 }else
			 if(event.type == SDL_KEYUP) {
				 keyState[event.key.keysym.sym] = false;
				 keyUpdate[event.key.keysym.sym] = 2;
				 updateCounter++;
			 }else
			 if(event.type == SDL_MOUSEBUTTONDOWN) {
				 mouseState[event.button.button] =  true;
				 mouseUpdate[event.button.button] = 1;
				 updateCounter++;
			 }else
		 	 if(event.type == SDL_MOUSEBUTTONUP) {
			 	 mouseState[event.button.button] =  false;
			 	 mouseUpdate[event.button.button] = 2;
			 	 updateCounter++;
		 	 }
		 }
    }
}

bool InputManager::KeyPress(int key){
	if(keyState.find(key) != keyState.end() && updateCounter == 1 &&
			keyUpdate[key] == 1 && keyState[key]== true) return true;
	return false;
}
bool InputManager::KeyRelease(int key){
	if(keyState.find(key) != keyState.end() && updateCounter == 2 &&
				keyUpdate[key] == 2 && keyState[key]== false) return true;
	return false;
}
bool InputManager::IsKeyDown(int key){
	return keyState[key];
}

bool InputManager::MousePress(int button){
	if(updateCounter == 1 && mouseUpdate[button] == 1 && mouseState[button]== true) return true;
	return false;
}
bool InputManager::MouseRelease(int button){
	if(updateCounter == 2 && mouseUpdate[button] == 2 && mouseState[button]== false) return true;
	return false;
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


