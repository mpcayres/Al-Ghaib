#ifndef INCLUDE_Player_HPP_
#define INCLUDE_Player_HPP_

#include "InventoryObject.hpp"
#include "GameObject.hpp"
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
	bool GetShowingInventory();
	void AddInventory(std::string obj/*, std::string objSp*/);
	//std::vector<std::unique_ptr<InventoryObject>> GetInventory();

	static Player * player;

private:
	Timer time;
	Sprite bodySp;
	Vec2 speed;
	int hp;
	bool running;

	int inHandIndex;
	bool showingInventory;
	std::vector<std::unique_ptr<InventoryObject>> inventory;
};

#endif /* INCLUDE_Player_HPP_ */
