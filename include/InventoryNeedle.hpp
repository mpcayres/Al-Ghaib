#ifndef INCLUDE_INVENTORYNEEDLE_HPP_
#define INCLUDE_INVENTORYNEEDLE_HPP_

#include "InventoryObject.hpp"

class InventoryNeedle : public InventoryObject {
public:
	InventoryNeedle();
	~InventoryNeedle();

	bool Action(GameObject* other);
	bool IsObject(std::string type);
	std::string GetObject();
};



#endif /* INCLUDE_INVENTORYNEEDLE_HPP_ */
