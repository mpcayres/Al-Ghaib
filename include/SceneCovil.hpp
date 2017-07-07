#ifndef SRC_SCENECOVIL_HPP_
#define SRC_SCENECOVIL_HPP_

#include "SceneObject.hpp"
#include <iostream>

class SceneCovil : public SceneObject {
public:
	SceneCovil(float x, float y);

	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool ReceiveAction(InventoryObject* other);

};

#endif /* SRC_SCENECOVIL_HPP_ */
