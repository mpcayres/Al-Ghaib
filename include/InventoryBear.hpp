#ifndef INCLUDE_INVENTORYBEAR_HPP_
#define INCLUDE_INVENTORYBEAR_HPP_

#include "InventoryObject.hpp"

#include <iostream>


class InventoryBear : public InventoryObject {
public:
	InventoryBear();
	~InventoryBear();

	void Render(int x, int y);
	bool Action(GameObject* other);
	bool IsObject(std::string type);
	std::string GetObject();
	int GetHeight();
	int GetWidth();
	void SetScaleX(float scale);
	void SetScaleY(float scale);

private:
	Sprite sp;
};



#endif /* INCLUDE_INVENTORYBEAR_HPP_ */
