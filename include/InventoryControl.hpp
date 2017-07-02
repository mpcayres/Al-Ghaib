#ifndef SRC_INVENTORYCONTROL_HPP_
#define SRC_INVENTORYCONTROL_HPP_

#include "InventoryObject.hpp"

class InventoryControl : public InventoryObject {
public:
	InventoryControl();
	~InventoryControl();

	bool Action(GameObject* other);
	bool IsObject(std::string type);
	std::string GetObject();
};

#endif /* SRC_INVENTORYCONTROL_HPP_ */
