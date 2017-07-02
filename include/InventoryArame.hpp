#ifndef SRC_INVENTORYARAME_HPP_
#define SRC_INVENTORYARAME_HPP_

#include "InventoryKey.hpp"

class InventoryArame : public InventoryKey {
public:
	InventoryArame();
	~InventoryArame();

	bool IsObject(std::string type);
	std::string GetObject();
};

#endif /* SRC_INVENTORYARAME_HPP_ */
