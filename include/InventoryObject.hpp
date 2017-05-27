#ifndef INCLUDE_INVENTORYOBJECT_HPP_
#define INCLUDE_INVENTORYOBJECT_HPP_

#include <string>

#include "Geometry.hpp"
#include "Sprite.hpp"

class InventoryObject{

public:
	virtual ~InventoryObject(){};

	virtual void Render(int x, int y) = 0;
	virtual void Action() = 0;
	virtual bool IsObject(std::string type) = 0;
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual void SetScaleX(float scale) = 0;
	virtual void SetScaleY(float scale) = 0;
};


#endif /* INCLUDE_INVENTORYOBJECT_HPP_ */
