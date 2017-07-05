#ifndef SRC_SCENEDOOR_HPP_
#define SRC_SCENEDOOR_HPP_

#include "SceneObject.hpp"
#include <iostream>

#define ABRE 0
//#define FECHA 2

class SceneDoor : public SceneObject {
public:
	SceneDoor(float x, float y, std::string dest, bool locked = true,
		std::string img = "img/cenario/geral/door-closed.png", std::string img2 = "img/cenario/geral/door-opened.png", int block = 0);

	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool ReceiveAction(InventoryObject* other);
	bool GetChangeState();
	void SetChangeState(bool change);
	std::string GetDest();
	//bool Tried();

	static int ValorPassar;
	static int count;

protected:
	int contador;
	bool lock;
	int blockArame;
	std::string dest;
	bool changeState;
	//bool tried;
};

#endif /* SRC_SCENEDOOR_HPP_ */
