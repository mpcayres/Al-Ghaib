#ifndef SRC_SCENEDOOR_HPP_
#define SRC_SCENEDOOR_HPP_

#include "SceneObject.hpp"
#include "Text.hpp"

class SceneDoor : public SceneObject {
public:
	SceneDoor(float x, float y, std::string dest,bool locked = true,
			std::string img = "img/scene-door-closed.png", std::string img2 = "img/scene-door-opened.png");

	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool ReceiveAction(InventoryObject* other);
	bool GetChangeState();
	void SetChangeState(bool change);
	std::string GetDest();
	//bool Tried();

private:
	bool lock;
	std::string dest;
	bool changeState;
	//bool tried;
};

#endif /* SRC_SCENEDOOR_HPP_ */
