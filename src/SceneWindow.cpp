#include "SceneWindow.hpp"
#include "MissionManager.hpp"

SceneWindow::SceneWindow(float x, float y, std::string img, std::string img2) :
	SceneObject(x, y, img, img2) { }

void SceneWindow::NotifyCollision(GameObject& other){
	SceneObject::NotifyCollision(other);
	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			if(estado){
				estado = false;
				sp.Open(change1);
				box.x = box.x + box.w/2 - sp.GetWidth()/2;
				box.y = box.y + box.h/2 - sp.GetHeight()/2;
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();
			} else{
				estado = true;
				sp.Open(change2);
				box.x = box.x + box.w/2 - sp.GetWidth()/2;
				box.y = box.y + box.h/2 - sp.GetHeight()/2;
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();

				//Nesse caso nao precisa no eixo y
				if((MissionManager::player->box.y + MissionManager::player->box.h - OFFSET_PISO < box.y + box.h)
					&& (MissionManager::player->GetDirecao() == Player::LESTE ||
						MissionManager::player->GetDirecao() == Player::OESTE)){

					if((MissionManager::player->box.x < box.x + box.w &&
							MissionManager::player->box.x + MissionManager::player->box.w > box.x + box.w )
							|| (box.InsideX(MissionManager::player->box) &&
									MissionManager::player->box.CenterX() >= box.CenterX())){
						MissionManager::player->box.x = box.x + box.w + 1;
					} else if((MissionManager::player->box.x + MissionManager::player->box.w > box.x &&
							MissionManager::player->box.x < box.x)
							|| (box.InsideX(MissionManager::player->box) &&
									MissionManager::player->box.CenterX() < box.CenterX())){
						MissionManager::player->box.x = box.x - MissionManager::player->box.w - 1;
					}

				}
			}
		}
	}
}

bool SceneWindow::Is(std::string type){
	return (type == "SceneWindow" || type == "CollidableObject");
}
