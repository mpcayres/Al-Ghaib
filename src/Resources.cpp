#include <iostream>

#include "Resources.hpp"
#include "Game.hpp"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>  Resources::soundTable;
std::unordered_map<std::string, std::shared_ptr<TTF_Font>> Resources::fontTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file){
	if(imageTable.find(file) == imageTable.end()){
		SDL_Texture* aux = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		if(aux != nullptr){
			imageTable.emplace(file, std::shared_ptr<SDL_Texture>(
					aux, [](SDL_Texture* texture){SDL_DestroyTexture(texture);}));
			return imageTable[file];
		} else{
			std::cout << "IMG_LoadTexture: " << SDL_GetError() << std::endl;
			return nullptr; //exit(1);
		}
	}
	return imageTable[file];
}

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file){
	if(musicTable.find(file) == musicTable.end()){
		Mix_Music* aux = Mix_LoadMUS(file.c_str());
		if(aux != nullptr){
			musicTable.emplace(file, std::shared_ptr<Mix_Music>(
					aux, [](Mix_Music* Music){Mix_FreeMusic(Music);}));
			return musicTable[file];
		} else{
			std::cout << "Mix_LoadMUS: " << SDL_GetError() << std::endl;
			return nullptr; //exit(1);
		}
	}
	return musicTable[file];
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file){
	if(soundTable.find(file) == soundTable.end()){
		Mix_Chunk*aux = Mix_LoadWAV(file.c_str());
		if(aux != nullptr){
			soundTable.emplace(file, std::shared_ptr<Mix_Chunk>(
					aux, [](Mix_Chunk* chunk){Mix_FreeChunk(chunk);}));
			return soundTable[file];
		} else{
			std::cout << "Mix_LoadWAV: " << SDL_GetError() << std::endl;
			return nullptr; //exit(1);
		}
	}
	return soundTable[file];
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int ptsize){
	std::string concat = file + std::to_string(ptsize);
	if(fontTable.find(concat) == fontTable.end()){
		TTF_Font* aux = TTF_OpenFont(file.c_str(), ptsize);
		if(aux != nullptr){
			fontTable.emplace(concat, std::shared_ptr<TTF_Font>(
					aux, [](TTF_Font* font){TTF_CloseFont(font);}));
			return fontTable[concat];
		} else{
			std::cout << "TTF_OpenFont: " << SDL_GetError() << std::endl;
			return nullptr; //exit(1);
		}
	}
	return fontTable[concat];;
}

void Resources::ClearImage(){
	for(std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator i = imageTable.begin();
		i != imageTable.end(); i++){
		if((*i).second.unique()){
			imageTable.erase(i);
		}
	}
	imageTable.clear();
}

void Resources::ClearMusic(){
	for(std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::iterator i = musicTable.begin();
		i != musicTable.end(); i++){
		if((*i).second.unique()){
			musicTable.erase(i);
		}
	}
	musicTable.clear();
}

void Resources::ClearSound(){
	for(std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::iterator i = soundTable.begin();
		i != soundTable.end(); i++){
		if((*i).second.unique()){
			soundTable.erase(i);
		}
	}
	soundTable.clear();
}

void Resources::ClearFont(){
	for(std::unordered_map<std::string, std::shared_ptr<TTF_Font>>::iterator i = fontTable.begin();
		i != fontTable.end(); i++){
		if((*i).second.unique()){
			fontTable.erase(i);
		}
	}
	fontTable.clear();
}

void Resources::ClearResources(){
	ClearImage();
	ClearMusic();
	ClearSound();
	ClearFont();
}
