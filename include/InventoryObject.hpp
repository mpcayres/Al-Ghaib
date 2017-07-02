#ifndef INCLUDE_INVENTORYOBJECT_HPP_
#define INCLUDE_INVENTORYOBJECT_HPP_

#include <string>

#include "Geometry.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"

class InventoryObject{

public:
	InventoryObject(std::string file);
	virtual ~InventoryObject();

	void Render(int x, int y);
	int GetWidth();
	int GetHeight();
	void SetScaleX(float scale);
	void SetScaleY(float scale);

	virtual bool Action(GameObject* other) = 0;
	virtual bool IsObject(std::string type) = 0;
	virtual std::string GetObject() = 0;

protected:
	Sprite sp;
};


#endif /* INCLUDE_INVENTORYOBJECT_HPP_ */
