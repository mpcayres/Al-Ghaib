#ifndef INCLUDE_INVENTORYKEY_HPP_
#define INCLUDE_INVENTORYKEY_HPP_

#include "InventoryObject.hpp"

class InventoryKey : public InventoryObject {
public:
	InventoryKey();
	~InventoryKey();

	void Render();
	void Action();
	bool IsObject(std::string type);

private:
	Sprite sp;
};



#endif /* INCLUDE_INVENTORYKEY_HPP_ */
