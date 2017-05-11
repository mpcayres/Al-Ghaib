#ifndef SPRITE_H_
#define SPRITE_H_

#ifdef _WIN32
	#include <SDL.h>
	#include <SDL_image.h>
#elif __APPLE__
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#elif __linux__
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#endif

#include <string>
#include <memory>

class Sprite {
public:
	Sprite();
	Sprite(std::string file, int frameCount = 1, float frameTime = 1);
	virtual ~Sprite();

	void Open(std::string file, int frameCount = 1, float frameTime = 1);
	void SetClip(int x, int y, int w, int h);
	void Render(int x, int y, float angle = 0);

	void Update(float dt);
	void SetFrame(int frame);
	void SetFrameCount(int frameCount);
	void SetFrameTime(int frameTime);

	int GetWidth();
	int GetHeight();
	bool IsOpen();

	void SetScaleX(float scale);
	void SetScaleY(float scale);

private:
	std::shared_ptr<SDL_Texture> texture;
	int width;
	int height;
	SDL_Rect clipRect;

	float scaleX;
	float scaleY;

	int frameCount;
	int currentFrame;
	float timeElapsed;
	float frameTime;
};

#endif /* SPRITE_H_ */
