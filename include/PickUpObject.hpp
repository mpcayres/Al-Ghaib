#ifndef SRC_STORAGEOBJECT_H_
#define SRC_STORAGEOBJECT_H_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Game.hpp"

#define OFFSET_SCREEN 10

class PickUpObject : public GameObject {
public:
	PickUpObject(float x, float y, std::string obj, std::string img);

	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	std::string obj;
	//std::string objSp;
	Sprite sp;
	bool dead;
	bool selected; //provavelmente vai mudar quando tiver o inventario
};

#endif /* SRC_STORAGEOBJECT_H_ */
