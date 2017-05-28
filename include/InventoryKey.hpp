#ifndef INCLUDE_INVENTORYKEY_HPP_
#define INCLUDE_INVENTORYKEY_HPP_

#include "InventoryObject.hpp"

class InventoryKey : public InventoryObject {
public:
	InventoryKey();
	~InventoryKey();

	void Render(int x, int y);
	bool Action(GameObject* other);
	bool IsObject(std::string type);
	int GetHeight();
	int GetWidth();
	void SetScaleX(float scale);
	void SetScaleY(float scale);

private:
	Sprite sp;
};



#endif /* INCLUDE_INVENTORYKEY_HPP_ */
