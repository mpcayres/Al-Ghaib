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
}

void Music::Stop(){
	Mix_FadeOutMusic(0);
}

void Music::Open(std::string file){
	music = Resources::GetMusic(file);
}

bool Music::IsOpen(){
	return(!(music == nullptr));
}
