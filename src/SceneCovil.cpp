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

void SceneCovil::ChangeImage(bool justOpen){
	if(change2 != ""){
		Sound s = Sound("audio/portapequenaconvertida.wav");
		s.Play(0);

		if(estado && !justOpen){
			estado = false;
			sp.Open(change1);
			if(box.w != sp.GetWidth()){
				box.x = box.x + box.w/2 - sp.GetWidth()/2 - 20;
				box.w = sp.GetWidth();
			}
			if(box.h != sp.GetHeight()){
				box.y = box.y + box.h/2 - sp.GetHeight()/2;
				box.h = sp.GetHeight();
			}
		} else if(!estado){
			estado = true;
			sp.Open(change2);
			int w = box.w; int h = box.h;
			if(box.w != sp.GetWidth()){
				box.x += box.w/2 - sp.GetWidth()/2 + 20;
				box.w = sp.GetWidth();
			}
			if(box.h != sp.GetHeight()){
				box.y += box.h/2 - sp.GetHeight()/2;
				box.h = sp.GetHeight();
			}

			MovePlayerColliding(w, h);
		}
	}
}

