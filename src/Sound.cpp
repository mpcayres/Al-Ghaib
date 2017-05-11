#include "Sound.h"
#include "Resources.h"

Sound::Sound(){
	chunk = nullptr;
	channel = -1;
}

Sound::Sound(std::string file){
	channel = -1;
	Open(file);
 }

void Sound::Play(int times){
	Mix_PlayChannel(channel, chunk.get(), times);
}

void Sound::Stop(){
	Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
	chunk = Resources::GetSound(file);
}

bool Sound::IsOpen(){
	return (chunk.get() != nullptr);
}