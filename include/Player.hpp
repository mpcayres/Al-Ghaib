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
#include <string>

class Player : public GameObject{
public:
	enum InvBox{SUL, NORTE, LESTE, OESTE};

	Player(float x, float y, int oldInHand = -1, std::vector<std::string> oldInventory = std::vector<std::string>());
	~Player();

	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);

	void SetPosition(int x, int y);
	void SetDirecao(int dir);
	bool CollidingPlayer(Rect box, int offset);
	void Running(InputManager InputInstance);

	void SetMovementLimits(Rect limits);
	void AddWallLimits(Rect limits);
	void ResetWallLimits();
	void ChangeHiddenState();
	void ChangeAboveObject();

	bool GetAboveObject();
	int GetDirecao();
	Vec2 GetSpeed();
	void SetDoor(bool value);
	bool GetDoor();

	void AddRuido(float add);
	float GetRuido();

	void AddInventory(std::string obj);
	std::vector<std::shared_ptr<InventoryObject>> GetInventory();
	std::vector<std::string> GetStringInventory();
	bool GetShowingInventory();
	std::shared_ptr<InventoryObject> GetInHand();
	int GetInHandIndex();
	void DeleteInventory();

	void RenderInventory();
	void RenderInHand();
	void RenderNoise();

	//Vec2 previousPos;
	Rect limits;
	std::vector<Rect> wallLimits;

private:
	Timer timeRuido, timeCooldown;
	Sprite spKinder, spKinderRun, spAnimKinder, spKinderPush;
	Sprite spInventory, spInventorybox, spInventoryboxSelected;
	Sprite spNoise;

	Vec2 speed;
	int hp;
	bool running;

	int inHandIndex, inventoryIndex;
	bool showingInventory;
	std::vector<std::shared_ptr<InventoryObject>> inventory;

	InvBox direcao;
	InputManager InputInstance;

	bool direcaoShift;
	bool door, hidden, animShowing, aboveObject;
	float ruido;
};

#endif /* INCLUDE_Player_HPP_ */
