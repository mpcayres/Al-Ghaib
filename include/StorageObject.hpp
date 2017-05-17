/*
 * StorageObject.h
 *
 *  Created on: 17 de mai de 2017
 *      Author: mp_ca
 */

#ifndef SRC_STORAGEOBJECT_H_
#define SRC_STORAGEOBJECT_H_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"

class StorageObject : public GameObject {
public:
	StorageObject(float x, float y, int id, std::string img);

	void Update(float dt);
	void Render();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	int id;
	Sprite sp;
	bool dead;
};

#endif /* SRC_STORAGEOBJECT_H_ */
