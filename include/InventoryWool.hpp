#ifndef INCLUDE_INVENTORYWOOL_HPP_
#define INCLUDE_INVENTORYWOOL_HPP_

#include "InventoryObject.hpp"

class InventoryWool : public InventoryObject {
public:
	InventoryWool();
	~InventoryWool();

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



#endif /* INCLUDE_INVENTORYWOOL_HPP_ */
