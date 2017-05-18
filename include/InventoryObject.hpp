#ifndef INCLUDE_INVENTORYOBJECT_HPP_
#define INCLUDE_INVENTORYOBJECT_HPP_

#include <string>

#include "Geometry.hpp"
#include "Sprite.hpp"

class InventoryObject{

public:
	virtual ~InventoryObject(){};

	virtual void Render() = 0;
	virtual void Action() = 0;
	virtual bool IsObject(std::string type) = 0;
};


#endif /* INCLUDE_INVENTORYOBJECT_HPP_ */
