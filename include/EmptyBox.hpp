#ifndef EMPTYBOX_HPP_
#define EMPTYBOX_HPP_

#include <string>

#include "Player.hpp"
#include "Geometry.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"

#define DISTANCIA	30
#define OFFSET		5

class EmptyBox : public GameObject {
public:
	EmptyBox();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);
	void setX(int x);
	void setY(int y);
private:
	InventoryObject* inHand;

};

#endif /* EMPTYBOX_H_ */
