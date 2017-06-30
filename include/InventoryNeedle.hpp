#ifndef INCLUDE_INVENTORYNEEDLE_HPP_
#define INCLUDE_INVENTORYNEEDLE_HPP_

#include "InventoryObject.hpp"

class InventoryNeedle : public InventoryObject {
public:
	InventoryNeedle();
	~InventoryNeedle();

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



#endif /* INCLUDE_INVENTORYNEEDLE_HPP_ */
