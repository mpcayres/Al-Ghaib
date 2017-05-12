/*
 * Music.cpp
 *
 *  Created on: 10 de mai de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#include "Music.hpp"
#include "Resources.hpp"

Music::Music(){
	music = nullptr;
}

Music::Music(std::string file){
	Open(file);
}

void Music::Play(int times){
	Mix_PlayMusic(music.get(), times);
	std::cout << "A";
}

void Music::Stop(){
	Mix_FadeOutMusic(0);
	std::cout << "B";
}

void Music::Open(std::string file){
	music = Resources::GetMusic(file);
	if(music == nullptr){
		printf("LoadMusic falhou: %s\n", SDL_GetError());
		exit(1);
	}

}

bool Music::IsOpen(){
	return(!(music == nullptr));
}




