#include "Resources.h"
#include "Game.h"
#include <iostream>

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file){
	if(imageTable.find(file) == imageTable.end()){
		SDL_Texture* texture = IMG_LoadTexture(
				Game::GetInstance().GetRenderer(), file.c_str());
		if(texture == nullptr){
			std::cout << SDL_GetError() << std::endl;
			exit(1);
		}
		imageTable.emplace(file, std::shared_ptr<SDL_Texture>(
					texture, [](SDL_Texture *tex){
						SDL_DestroyTexture(tex);
					} )
		);
	}
	std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator it = imageTable.find(file);
	return it->second;
}

void Resources::ClearImages(){
	for(std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator it =
			imageTable.begin(); it != imageTable.end(); ){
		if((*it).second.unique())
			it = imageTable.erase(it);
		else it++;
	}

	imageTable.clear();
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file){
	if(musicTable.find(file) == musicTable.end()){
		Mix_Music* music = Mix_LoadMUS(file.c_str());
		if(music == nullptr){
			std::cout << SDL_GetError() << std::endl;
			exit(1);
		}
		musicTable.emplace(file, std::shared_ptr<Mix_Music>(
					music, [](Mix_Music *mix){
						Mix_FreeMusic(mix);
					} )
		);
	}
	std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::iterator it = musicTable.find(file);
	return it->second;
}

void Resources::ClearMusic(){
	for(std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::iterator it =
			musicTable.begin(); it != musicTable.end(); ){
		if((*it).second.unique())
			it = musicTable.erase(it);
		else it++;
	}

	musicTable.clear();
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file){
	if(soundTable.find(file) == soundTable.end()){
		Mix_Chunk* sound = Mix_LoadWAV(file.c_str());
		if(sound == nullptr){
			std::cout << SDL_GetError() << std::endl;
			exit(1);
		}
		soundTable.emplace(file, std::shared_ptr<Mix_Chunk>(
				sound, [](Mix_Chunk *mix){
						Mix_FreeChunk(mix);
					} )
		);
	}
	std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::iterator it = soundTable.find(file);
	return it->second;
}

void Resources::ClearSounds(){
	for(std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::iterator it =
			soundTable.begin(); it != soundTable.end(); ){
		if((*it).second.unique())
			it = soundTable.erase(it);
		else it++;
	}

	soundTable.clear();
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize){
	std::string auxFile = file + std::to_string(fontSize);
	if(fontTable.find(auxFile) == fontTable.end()){
		TTF_Font* font = TTF_OpenFont(file.c_str(), fontSize);
		if(font == nullptr){
			std::cout << SDL_GetError() << std::endl;
			exit(1);
		}
		fontTable.emplace(auxFile, std::shared_ptr<TTF_Font>(
				font, [](TTF_Font *ttf){
						TTF_CloseFont(ttf);
					} )
		);
	}
	std::unordered_map<std::string, std::shared_ptr<TTF_Font>>::iterator it = fontTable.find(auxFile);
	return it->second;
}

void Resources::ClearFonts(){
	for(std::unordered_map<std::string, std::shared_ptr<TTF_Font>>::iterator it =
			fontTable.begin(); it != fontTable.end(); ){
		if((*it).second.unique())
			it = fontTable.erase(it);
		else it++;
	}

	soundTable.clear();
}

void Resources::ClearResources(){
	ClearImages();
	ClearMusic();
	ClearSounds();
	ClearFonts();
}