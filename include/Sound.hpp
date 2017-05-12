#ifndef INCLUDE_SOUND_HPP_
#define INCLUDE_SOUND_HPP_

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

class Sound{
public:
	Sound();
	Sound(std::string file);

	void Play(int times);
	void Stop();
	void Open(std::string file);
	bool IsOpen();

private:
	std::shared_ptr<Mix_Chunk> chunk;
	int channel;

};

#endif /* INCLUDE_SOUND_HPP_ */
