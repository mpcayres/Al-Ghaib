#ifndef SRC_SCENEUNTOUCHABLE_HPP_
#define SRC_SCENEUNTOUCHABLE_HPP_

#include <string>

#include "GameObject.hpp"
#include "Sprite.hpp"
#include "InventoryObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"
#include "MovingObject.hpp"

class SceneUntouchable : public GameObject {
public:
	//enum CaseChange{DEFAULT, SAMEY_DOWN, SAMEY_UP, SAMEX};
	SceneUntouchable(float x, float y, std::string img, float rot = 0,
			float scaleX = 1, float scaleY = 1);

	void Update(float dt);
	void Render();
	bool IsDead();
	bool NotifyCollision(GameObject& other);
	bool Is(std::string type);
	//bool GetBlockRandom();
	//bool GetState();
	//void ChangeImage();
	//void MovePlayerColliding(float w, float h);

protected:
	Sprite sp;
	//bool estado, blockRandom;
	//std::string change1, change2, objCreate;
	//float offset;
	//CaseChange caseChange;
};

#endif  /* SCENEUNTOUCHABLE_H_ */
