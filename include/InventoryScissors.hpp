#ifndef INCLUDE_INVENTORYSCISSORS_HPP_
#define INCLUDE_INVENTORYSCISSORS_HPP_

#include "InventoryObject.hpp"

class InventoryScissors : public InventoryObject {
public:
	InventoryScissors();
	~InventoryScissors();

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



#endif /* INCLUDE_INVENTORYSCISSORS_HPP_ */
