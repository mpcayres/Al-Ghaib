#ifndef SRC_INVENTORYBOOK_HPP_
#define SRC_INVENTORYBOOK_HPP_

#include "InventoryObject.hpp"

class InventoryBook : public InventoryObject {
public:
	InventoryBook();
	~InventoryBook();
	bool Action(GameObject* other);

	bool IsObject(std::string type);
	std::string GetObject();

private:
	int timesPressed;
};

#endif /* SRC_INVENTORYBOOK_HPP_ */
