#ifdef __APPLE__
	#include <SDL2.h>
	#include <SDL_imagem/SDL_image.h>
#elif __linux__
    	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#elif _WIN32
	#include "SDL.h"
	#include "SDL_image.h"
#else

#endif

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"


#ifndef INCLUDE_Player_HPP_
#define INCLUDE_Player_HPP_

class Player : public GameObject{
public:
	Player(float x, float y);
	~Player();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	void Shoot();
	bool Is(std::string type);

	static Player * player;


private:
	Timer time;
	Sprite bodySp;
	Vec2 speed;
	int hp;
};




#endif /* INCLUDE_Player_HPP_ */
