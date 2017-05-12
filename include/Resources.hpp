#ifndef INCLUDE_RESOURCES_HPP_
#define INCLUDE_RESOURCES_HPP_

#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
	#include <SDL_mixer/SDL_mixer.h>
	#include <SDL_ttf/SDL_ttf.h>
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_ttf.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
#endif

#include <string>
#include <unordered_map>
#include <memory>

class Resources{
public:
	static std::shared_ptr<SDL_Texture> GetImage(std::string file);
	static std::shared_ptr<Mix_Music> GetMusic(std::string file);
	static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
	static std::shared_ptr<TTF_Font> GetFont(std::string file, int ptsize);

	static void ClearImage();
	static void ClearMusic();
	static void ClearSound();
	static void ClearFont();

	static void ClearResources();

private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
	static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;

};

#endif /* INCLUDE_RESOURCES_HPP_ */
