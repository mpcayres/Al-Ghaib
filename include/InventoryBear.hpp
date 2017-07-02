#ifndef INCLUDE_INVENTORYBEAR_HPP_
#define INCLUDE_INVENTORYBEAR_HPP_

#include "InventoryObject.hpp"

class InventoryBear : public InventoryObject {
public:
	InventoryBear();
	~InventoryBear();

	bool Action(GameObject* other);
	bool IsObject(std::string type);
	std::string GetObject();
};



#endif /* INCLUDE_INVENTORYBEAR_HPP_ */
