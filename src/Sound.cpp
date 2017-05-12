/*
 * Sound.cpp
 *
 *  Created on: 11 de mai de 2017
 *      Author: renne
 */

#include "Sound.hpp"
#include "Resources.hpp"

Sound::Sound(){
	channel = -1;
	chunk = nullptr;
}

Sound::Sound(std::string file){
	Open(file);
}

void Sound::Play(int times){
	channel = Mix_PlayChannel(-1 ,chunk.get(), times);
}

void Sound::Stop(){
	Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
	chunk = Resources::GetSound(file);
	if(chunk == nullptr){
		printf("LoadSound falhou: %s\n", SDL_GetError());
		exit(1);
	}

}

bool Sound::IsOpen(){
	return(!(chunk == nullptr));
}


