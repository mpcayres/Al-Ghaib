#ifndef INCLUDE_INVENTORYSCISSORS_HPP_
#define INCLUDE_INVENTORYSCISSORS_HPP_

#include "InventoryObject.hpp"

class InventoryScissors : public InventoryObject {
public:
	InventoryScissors();
	~InventoryScissors();

	bool Action(GameObject* other);
	bool IsObject(std::string type);
	std::string GetObject();
};



#endif /* INCLUDE_INVENTORYSCISSORS_HPP_ */
