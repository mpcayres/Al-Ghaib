#ifndef INCLUDE_Player_HPP_
#define INCLUDE_Player_HPP_

#include "InventoryObject.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
//#include "Timer.hpp"
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
	void RenderInventory();

	int GetDirecao();
	Vec2 GetSpeed();

	static Player * player;
	Vec2 previousPos;
	enum InvBox{SUL, NORTE, LESTE, OESTE, NONE};

private:
	//Timer time;
	float timeAnim;
	Sprite sp;
	Sprite spInventory, spInventorybox, spInventoryboxSelected;

	Vec2 speed;
	int hp;
	bool running;

	int inHandIndex;
	bool showingInventory;
	std::vector<InventoryObject*> inventory;

	InvBox direcao;
	InvBox dirCollision;
	bool colliding;

};

#endif /* INCLUDE_Player_HPP_ */
