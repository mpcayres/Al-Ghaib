#ifndef SRC_SCENEDOOR_HPP_
#define SRC_SCENEDOOR_HPP_

#include "SceneObject.hpp"

class SceneDoor : public SceneObject {
public:
	SceneDoor(float x, float y, std::string img, std::string img2);

	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool ReceiveAction(InventoryObject* other);
	static bool GetChangeState();
	static void SetChangeState(bool t);

private:
	bool lock;
	static bool changeState;
};

#endif /* SRC_SCENEDOOR_HPP_ */
