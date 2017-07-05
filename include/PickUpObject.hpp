#ifndef SRC_STORAGEOBJECT_H_
#define SRC_STORAGEOBJECT_H_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Game.hpp"

#define OFFSET_SCREEN 10

class PickUpObject : public GameObject {
public:
	PickUpObject(float x, float y, std::string obj, std::string img, bool bloq = false, float scaleX = 1, float scaleY = 1, bool hide = false);

	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	std::string obj;
	Sprite sp;
	bool dead, bloqPick, hide;
};

#endif /* SRC_STORAGEOBJECT_H_ */
