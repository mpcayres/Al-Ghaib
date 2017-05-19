/*
 * EmptyBox.h
 *
 *  Created on: May 18, 2017
 *      Author: ingrid
 */

#ifndef EMPTYBOX_HPP_
#define EMPTYBOX_HPP_

#include <string>

#include "Player.hpp"
#include "Geometry.hpp"
#include "Sprite.hpp"
#include "GameObject.hpp"
#define DISTANCIA 50

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
	Timer time;
//private:
	//Rect box;
	//Sprite sp;
};

#endif /* EMPTYBOX_H_ */
