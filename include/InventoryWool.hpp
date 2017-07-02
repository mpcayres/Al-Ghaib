#ifndef INCLUDE_INVENTORYWOOL_HPP_
#define INCLUDE_INVENTORYWOOL_HPP_

#include "InventoryObject.hpp"

class InventoryWool : public InventoryObject {
public:
	InventoryWool();
	~InventoryWool();

	bool Action(GameObject* other);
	bool IsObject(std::string type);
	std::string GetObject();
};



#endif /* INCLUDE_INVENTORYWOOL_HPP_ */
