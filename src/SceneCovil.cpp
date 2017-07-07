#include "SceneCovil.hpp"
#include "MissionManager.hpp"
#include "Mission.hpp"
#include "Player.hpp"

SceneCovil::SceneCovil(float x, float y) :
	SceneObject(x, y, "img/cenario/mae/porao-fechado.png", "img/cenario/mae/porao-aberto.png", 0, 0.6, 0.6) {
	offset = 0;
}

bool SceneCovil::NotifyCollision(GameObject& other){
	if(!(other.Is("EmptyBox"))){
		SceneObject::NotifyCollision(other);
		return false;
	}

	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().KeyPress(Z_KEY) ){
			ChangeImage();
			MissionManager::missionManager->GetMission()->bronca = true;
		}
	}

	return false;
}

bool SceneCovil::Is(std::string type){
	return (type == "SceneCovil" || type == "CollidableObject");
}

bool SceneCovil::ReceiveAction(InventoryObject* other){
	return false;
}


