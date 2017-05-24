#ifndef SRC_STORAGEOBJECT_H_
#define SRC_STORAGEOBJECT_H_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"

class PickUpObject : public GameObject {
public:
	PickUpObject(float x, float y, std::string obj, std::string img);

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	std::string obj;
	//std::string objSp;
	Sprite sp;
	bool dead;
};

#endif /* SRC_STORAGEOBJECT_H_ */