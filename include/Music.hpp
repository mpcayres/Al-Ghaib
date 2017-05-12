#ifndef INCLUDE_MUSIC_HPP_
#define INCLUDE_MUSIC_HPP_

#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_mixer/SDL_mixer.h>
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_mixer.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_mixer.h"
#endif

#include <string>
#include <memory>

class Music{
public:
	Music();
	Music(std::string file);

	void Play(int times);
	void Stop();
	void Open(std::string file);
	bool IsOpen();

private:
	std::shared_ptr<Mix_Music> music;

};

#endif /* INCLUDE_MUSIC_HPP_ */
