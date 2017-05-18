#ifndef INCLUDE_Player_HPP_
#define INCLUDE_Player_HPP_

#include "GameObject.hpp"
#include "InventaryObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include <vector>
#include <memory>

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
	bool getRunning();
	bool GetShowingInventary();
	std::vector<std::unique_ptr<InventaryObject>> GetInventary();

	static Player * player;

private:
	std::vector<std::unique_ptr<InventaryObject>> inventary;
	int inHandIndex;
	Timer time;
	Sprite bodySp;
	Vec2 speed;
	int hp;
	bool running;

	bool showingInventary;
};

#endif /* INCLUDE_Player_HPP_ */
