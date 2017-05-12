/*
 * Resources.cpp
 *
 *  Created on: 23 de mar de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#include "Resources.hpp"
#include "Game.hpp"
#include <cstdint>
#include <string>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>  Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;



std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file){
	SDL_Texture* aux;
	std::shared_ptr<SDL_Texture> N;
	if(imageTable.find(file) == imageTable.end()){
		aux = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		if(aux != NULL)
		imageTable.emplace(file,
				std::shared_ptr<SDL_Texture>(aux,[](SDL_Texture* texture){SDL_DestroyTexture(texture);}));
		return imageTable[file];
	}
	return imageTable[file];
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file){
	Mix_Music* aux;
	std::shared_ptr<Mix_Music> N;
	if(musicTable.find(file) == musicTable.end()){
		aux = Mix_LoadMUS(file.c_str());
		if(aux != NULL)
		musicTable.emplace(file,
				std::shared_ptr<Mix_Music>(aux,[](Mix_Music* Music){Mix_FreeMusic(Music);}));
		return musicTable[file];
	}
	return musicTable[file];
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file){
	Mix_Chunk* aux;
	std::shared_ptr<Mix_Chunk> N;
	if(soundTable.find(file) == soundTable.end()){
		aux = Mix_LoadWAV(file.c_str());
		if(aux != NULL)
		soundTable.emplace(file,
				std::shared_ptr<Mix_Chunk>(aux,[](Mix_Chunk* chunk){Mix_FreeChunk(chunk);}));
		return soundTable[file];
	}
	return soundTable[file];
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int ptsize){
	TTF_Font* aux;
	std::shared_ptr<TTF_Font> N;

	std::string concat = file + std::to_string(ptsize);
	if(fontTable.find(concat) == fontTable.end()){
		aux = TTF_OpenFont(file.c_str(), ptsize);
		if(aux == NULL){
				printf("SDL_CreateTextureFromSurface falhou: %s\n", SDL_GetError());
				exit(1);
			}
		fontTable.emplace(concat,
				std::shared_ptr<TTF_Font>(aux,[](TTF_Font* font){TTF_CloseFont(font);}));
		return fontTable[concat];
	}
	return fontTable[concat];;
}

void Resources::ClearImages(){
	for(std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator i = imageTable.begin();
		i!= imageTable.end();i++){
		if((*i).second.unique()){
			imageTable.erase(i);
		}
	}
	imageTable.clear();
}

void Resources::ClearMusic(){
	for(std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::iterator i = musicTable.begin();
		i!= musicTable.end();i++){
		if((*i).second.unique()){
			musicTable.erase(i);
		}
	}
	musicTable.clear();
}

void Resources::ClearSound(){
	for(std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::iterator i = soundTable.begin();
		i!= soundTable.end();i++){
		if((*i).second.unique()){
			soundTable.erase(i);
		}
	}
	soundTable.clear();
}

void Resources::ClearFont(){
	for(std::unordered_map<std::string, std::shared_ptr<TTF_Font>>::iterator i = fontTable.begin();
		i!= fontTable.end();i++){
		if((*i).second.unique()){
			fontTable.erase(i);
		}
	}
	fontTable.clear();
}



