#ifndef CAT_Player_HPP_
#define CAT_Player_HPP_

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Geometry.hpp"
#include "Player.hpp"
#include "EmptyBox.hpp"
#include <iostream>
#define VALUE 3
#define SPEED_CONTROL 3
#define Cat_COOLDOWN 3
#define MOV_OFFSET 1

class Cat : public GameObject {
public:
	enum InvBox{LESTE, OESTE, SUL, NORTE};
	Cat(float x, float y);
	~Cat();

	void Update(float dt);
	void SetPosition(float x, float y);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	void Shoot();
	bool Is(std::string type);
	//void Pursuit();
	void DefinedPath();
	void SetDestinationPath(Vec2 path);
	void SetDirecao(int dir);

	//Vec2 previousPos;
	bool show, seen, arrived, attractedWool, attractedTV;

private:
	Timer time;
	Sprite sp;
	Vec2 speed;
	//bool seen;
	Vec2 destination;
	//Vec2 destinationPath;
	std::vector<Vec2> destinationPath;

	//InvBox direcao;
};

#endif /* INCLUDE_Cat_HPP_ */
