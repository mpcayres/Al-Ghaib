#ifndef INCLUDE_INVENTORYMINIGAME_HPP_
#define INCLUDE_INVENTORYMINIGAME_HPP_

#include "InventoryObject.hpp"

class InventoryMiniGame : public InventoryObject {
public:
	InventoryMiniGame(std::string file);
	~InventoryMiniGame();

	void Render(int x, int y);
	bool Action(GameObject* other);
	bool IsObject(std::string type);
	std::string GetObject();
	int GetHeight();
	int GetWidth();
	void SetScaleX(float scale);
	void SetScaleY(float scale);

protected:
	Sprite sp;
	int timesPressed;
};

#endif /* INCLUDE_INVENTORYMINIGAME_HPP_ */
