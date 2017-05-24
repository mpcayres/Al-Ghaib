#ifndef INCLUDE_SPRITE_HPP_
#define INCLUDE_SPRITE_HPP_

#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include <string>
#include <memory>

class Sprite{
public:
	Sprite();
	Sprite(std::string file, int frameCount = 1, float frameTime = 1, int tamCount = 1);
	~Sprite();

	void SetScaleX(float scale);
	void SetScaleY(float scale);

	void Update(float dt, int posH = 0);
	void SetFrame(int frame, int posH = 0);
	void SetFrameCount(int frameCount);
	void SetFrameTime(float frameTime);

	void Open(std::string file, int frameCount = 1, float frameTime = 1, int tamCount = 1);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y, float angle);
	int GetWidth();
	int GetHeight();
	int GetScaledWidth();
	int GetScaledHeight();
	bool IsOpen();

private:
	std::shared_ptr<SDL_Texture> texture;
	int width, height;
	SDL_Rect clipRect;
	float scaleX;
	float scaleY;

	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
	int tamCount;
};

#endif /* INCLUDE_SPRITE_HPP_ */
