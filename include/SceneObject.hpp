#ifndef SRC_SCENEOBJECT_HPP_
#define SRC_SCENEOBJECT_HPP_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "InventoryObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"
#include "MovingObject.hpp"

class SceneObject : public GameObject {
public:
	enum CaseChange{DEFAULT, SAMEY_DOWN, SAMEY_UP, SAMEX};
	SceneObject(float x, float y, std::string img, std::string img2, float rot = 0, float scaleX = 1, float scaleY = 1, std::string create = "", int change = 0);

	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);
	bool GetCreateObject();
	bool GetState();
	void ChangeImage();
	void MovePlayerColliding(float w, float h);

protected:
	Sprite sp;
	bool estado;
	std::string change1, change2, objCreate;
	float offset;
	CaseChange caseChange;
};

#endif  /* SCENEOBJECT_H_ */
