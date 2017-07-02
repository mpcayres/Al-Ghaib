#include "ScenePortal.hpp"
#include "MissionManager.hpp"
#include "Mission.hpp"
#include "Player.hpp"

ScenePortal::ScenePortal(float x, float y, std::string dest, std::string img) :
	SceneDoor(x, y, dest, false, img, img) { }

bool ScenePortal::NotifyCollision(GameObject& other){
	if(!(other.Is("EmptyBox") || other.Is("Bear") || other.Is("Enemy"))){
		SceneObject::NotifyCollision(other);
		return false;
	}

	if((other.Is("Bear") || other.Is("Enemy")) && ValorPassar!=0 ){
		count ++;
	}

	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().IsKeyDown(LCTRL_KEY) &&
				InputManager::GetInstance().KeyPress(Z_KEY)){

			changeState = true;

		}
	}

	return false;
}

bool ScenePortal::Is(std::string type){
	return (type == "ScenePortal" || type == "SceneDoor" || type == "CollidableObject");
}

bool ScenePortal::ReceiveAction(InventoryObject* other){
	return false;
}
