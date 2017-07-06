#ifndef SRC_INVENTORYLINE_HPP_
#define SRC_INVENTORYLINE_HPP_

#include "InventoryObject.hpp"

class InventoryLine : public InventoryObject {
public:
	InventoryLine();
	~InventoryLine();
	bool Action(GameObject* other);

	bool IsObject(std::string type);
	std::string GetObject();

private:
	int timesPressed;
};

#endif /* SRC_INVENTORYLINE_HPP_ */
