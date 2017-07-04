#ifndef BEAR_Player_HPP_
#define BEAR_Player_HPP_

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Geometry.hpp"
#include "Player.hpp"
#include "EmptyBox.hpp"
#include <iostream>
#define VALUE 3
#define SPEED_CONTROL 3
#define Bear_COOLDOWN 3
#define MOV_OFFSET 1


class Bear : public GameObject {
public:
	enum InvBox{SUL, NORTE, LESTE, OESTE};
	Bear(float x, float y);
	~Bear();

	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	void Shoot();
	bool Is(std::string type);
	//void Pursuit();
	void DefinedPath();
	void SetDestinationPath(Vec2 path);
	void SetDirecao(int dir);

	static Bear * bear;

	//Vec2 previousPos;

	static bool show, seen;
	static bool arrived;
	static bool repair;
	static bool retorno;
private:
	Timer time;
	float offset;
	Sprite sp;
	Vec2 speed;
	int hp;
	//bool seen;
	Vec2 destination;
	//Vec2 destinationPath;
	std::vector<Vec2> destinationPath;

	InvBox direcao;

	bool direcaoShift/*, stop*/;

};

#endif /* INCLUDE_Bear_HPP_ */
