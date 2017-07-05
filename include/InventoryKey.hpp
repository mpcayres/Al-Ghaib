#ifndef INCLUDE_INVENTORYKEY_HPP_
#define INCLUDE_INVENTORYKEY_HPP_

#include "InventoryObject.hpp"

class InventoryKey : public InventoryObject {
public:
	InventoryKey(std::string file = "img/inventario/key.png");
	~InventoryKey();

	bool Action(GameObject* other);
	bool IsObject(std::string type);
	std::string GetObject();
};



#endif /* INCLUDE_INVENTORYKEY_HPP_ */
