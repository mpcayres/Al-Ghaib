/*


 * SceneObject.hpp
 *
 *  Created on: May 18, 2017
 *      Author: ingrid
 */
#ifndef SRC_SCENEOBJECT_HPP_
#define SRC_SCENEOBJECT_HPP_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"

class SceneObject : public GameObject {
public:
	SceneObject(float x, float y, int id, std::string img);

	void Update(float dt);
	void Render();
	bool IsEstado();
	bool IsDead();
	void NotifyCollision(GameObject& other);
	bool Is(std::string type);

private:
	int id;
	Sprite sp;
	bool estado;
};

#endif  /* SCENEOBJECT_H_ */
