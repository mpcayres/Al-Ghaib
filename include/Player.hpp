#ifndef INCLUDE_Player_HPP_
#define INCLUDE_Player_HPP_

#include "InventoryObject.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Timer.hpp"

#include "InputManager.hpp"
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
	void SetPosition(int x, int y);
	void Running(InputManager InputInstance);
	bool Is(std::string type);
	float GetRuido();
	bool GetShowingInventory();
	void AddInventory(std::string obj/*, std::string objSp*/);
	void RenderInventory();
	void RenderInHand();
	void RenderNoise();

	InventoryObject* GetInHand();
	void DeleteInventory();
	void SetMovementLimits(Rect limits);

	int GetDirecao();
	Vec2 GetSpeed();

	static Player * player;
	Vec2 previousPos;
	enum InvBox{SUL, NORTE, LESTE, OESTE};

private:
	Timer time;
	Sprite spKinder, spKinderRun;
	Sprite spInventory, spInventorybox, spInventoryboxSelected;
	Sprite spNoise;

	Vec2 speed;
	int hp;
	bool running;

	int inHandIndex, inventoryIndex;
	bool showingInventory;
	std::vector<InventoryObject*> inventory;

	InvBox direcao;
	InputManager InputInstance;
	bool direcaoShift;

	float ruido;

	Rect limits;
};

#endif /* INCLUDE_Player_HPP_ */
