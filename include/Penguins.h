#ifndef SRC_PENGUINS_H_
#define SRC_PENGUINS_H_

#include "GameObject.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Timer.h"

class Penguins : public GameObject {
public:
	Penguins(float x, float y);
	virtual ~Penguins();

	void Update(float dt);
	void Render();
	bool IsDead();
	void Shoot();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

	static Penguins* player;

private:
	Sprite bodySp;
	Sprite cannonSp;
	Vec2 speedSp;
	float linearSpeed;
	float cannonAngle;
	int hp;
	Timer timer;

};

#endif /* SRC_PENGUINS_H_ */
