#ifndef INCLUDE_INVENTORYMINIGAME_HPP_
#define INCLUDE_INVENTORYMINIGAME_HPP_

#include "InventoryObject.hpp"

class InventoryMiniGame : public InventoryObject {
public:
	InventoryMiniGame(std::string file, std::string file2, std::string file3);
	~InventoryMiniGame();

	bool Action(GameObject* other);
	bool IsObject(std::string type);
	std::string GetObject();

protected:
	std::string file2, file3;
	int timesPressed;
};

#endif /* INCLUDE_INVENTORYMINIGAME_HPP_ */
