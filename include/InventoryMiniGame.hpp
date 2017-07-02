#ifndef INCLUDE_INVENTORYMINIGAME_HPP_
#define INCLUDE_INVENTORYMINIGAME_HPP_

#include "InventoryObject.hpp"

class InventoryMiniGame : public InventoryObject {
public:
	InventoryMiniGame(std::string file, std::string file2, std::string file3);
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
	Sprite sp, sp2, sp3;
	int timesPressed;
};

#endif /* INCLUDE_INVENTORYMINIGAME_HPP_ */
