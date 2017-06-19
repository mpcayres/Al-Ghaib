#ifndef ENEMY_Player_HPP_
#define ENEMY_Player_HPP_

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "Timer.hpp"
#include "Geometry.hpp"
#include "Player.hpp"
#include "EmptyBox.hpp"
#include <iostream>
#define  VALUE 3
#define SPEED_CONTROL 3
#define ENEMY_COOLDOWN 3
#define MOV_OFFSET 1

class Enemy : public GameObject{
public:
	//enum InvBox{LESTE, OESTE, SUL, NORTE};
	Enemy(float x, float y);
	~Enemy();

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	void Shoot();
	bool Is(std::string type);
	void Pursuit();
	void DefinedPath();
	void SetDestinationPath(Vec2 path);
	void SetDirecao(int dir);
	//int GetDirecao();

	static Enemy * enemy;
	InvBox direcao;
	//Vec2 previousPos;

	static bool show;
	static bool arrived;
private:
	Timer time;
	Sprite sp;
	Vec2 speed;
	int hp;
	bool seen;
	Vec2 destination;
	//Vec2 destinationPath;
	std::vector<Vec2> destinationPath;



	bool direcaoShift;
};

#endif /* INCLUDE_Enemy_HPP_ */
