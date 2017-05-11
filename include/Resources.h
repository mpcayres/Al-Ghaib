#ifndef RESOURCES_H_
#define RESOURCES_H_

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
	#include <SDL_mixer.h>
	#include <SDL_ttf.h>
#elif __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_mixer/SDL_mixer.h>
	#include <SDL2_mixer/SDL_mixer.h>
	#include <SDL2_ttf/SDL_ttf.h>
#elif __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
	#include <SDL2/SDL_mixer.h>
	#include <SDL2/SDL_ttf.h>
#endif

#include <string>
#include <unordered_map>
#include <memory>

class Resources {
public:
	static std::shared_ptr<SDL_Texture> GetImage(std::string file);
	static void ClearImages();
	static std::shared_ptr<Mix_Music> GetMusic(std::string file);
	static void ClearMusic();
	static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
	static void ClearSounds();
	static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
	static void ClearFonts();
	static void ClearResources();

private:
	static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
	static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
	static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;
};

#endif /* RESOURCES_H_ */
