#ifndef SRC_SCENEPORTAL_HPP_
#define SRC_SCENEPORTAL_HPP_

#include "SceneDoor.hpp"
#include <iostream>

class ScenePortal : public SceneDoor {
public:
	ScenePortal(float x, float y, std::string dest, std::string img = "img/cenario/geral/portal.png");

	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool ReceiveAction(InventoryObject* other);

};

#endif /* SRC_SCENEPORTAL_HPP_ */
