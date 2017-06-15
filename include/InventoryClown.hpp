#ifndef INCLUDE_INVENTORYCLOWN_HPP_
#define INCLUDE_INVENTORYCLOWN_HPP_

#include "InventoryMiniGame.hpp"

class InventoryClown : public InventoryMiniGame {
public:
	InventoryClown();
	~InventoryClown();

	bool IsObject(std::string type);
	std::string GetObject();
};

#endif /* INCLUDE_INVENTORYCLOWN_HPP_ */
