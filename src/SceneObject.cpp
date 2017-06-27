#include "SceneObject.hpp"
#include "MissionManager.hpp"

SceneObject::SceneObject(float x, float y, std::string img, std::string img2,
		float rot, float scaleX, float scaleY, std::string create, int change) :
	sp(img) {
	sp.SetScaleX(scaleX); sp.SetScaleY(scaleY);
	change1 = img;
	change2 = img2;
	estado = false;
	rotation = rot;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	objCreate = create;
	offset = box.h/3;
	caseChange = (CaseChange) change;
}

bool SceneObject::IsDead(){
	return false;
}

void SceneObject::Update(float dt){

}

void SceneObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool SceneObject::NotifyCollision(GameObject& other){
	if(other.Is("Player")){
		return MissionManager::player->CollidingPlayer(box, offset);
	}

	if (other.Is("Enemy")){
		if(other.box.y + other.box.h - offset < box.y + box.h){

			if((other.box.x < box.x + box.w &&
					other.box.x + other.box.w > box.x + box.w )
					|| (box.InsideX(other.box) &&
					other.box.CenterX() >= box.CenterX())){
								other.box.x = box.x + box.w + 1;
			} else if((other.box.x + other.box.w > box.x &&
					other.box.x < box.x)
					|| (box.InsideX(MissionManager::player->box) &&
					other.box.CenterX() < box.CenterX())){
							other.box.x = box.x - other.box.w - 1;
			}

		}
	}

	if(other.Is("EmptyBox")){
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			if(objCreate != ""){
				MissionManager::player->AddInventory(objCreate);
				objCreate = "";
			}
			ChangeImage();
		}
	}

	return false;
}

bool SceneObject::Is(std::string type){
	return (type == "SceneObject" || type == "CollidableObject");
}

bool SceneObject::GetCreateObject(){
	return (objCreate != "");
}

bool SceneObject::GetState(){
	return estado;
}

void SceneObject::ChangeImage(){
	if(estado){
		estado = false;
		sp.Open(change1);
		switch(caseChange){
			case SAMEX:
				if(box.w != sp.GetWidth()){
					box.x += box.w - sp.GetWidth();
					box.w = sp.GetWidth();
				}
				box.h = sp.GetHeight();
				break;
			case SAMEY_UP:
				box.w = sp.GetWidth();
				if(box.h != sp.GetHeight()){
					box.y += box.h - sp.GetHeight();
					box.h = sp.GetHeight();
				}
				break;
			case DEFAULT:
				if(box.w != sp.GetWidth()){
					box.x = box.x + box.w/2 - sp.GetWidth()/2;
					box.w = sp.GetWidth();
				}
				if(box.h != sp.GetHeight()){
					box.y = box.y + box.h/2 - sp.GetHeight()/2;
					box.h = sp.GetHeight();
				}
				break;
			default:
				break;
		}
	} else{
		estado = true;
		sp.Open(change2);
		int w = box.w; int h = box.h;
		switch(caseChange){
			case SAMEX:
				if(box.w != sp.GetWidth()){
					box.x += box.w - sp.GetWidth();
					box.w = sp.GetWidth();
				}
				box.h = sp.GetHeight();
				break;
			case SAMEY_DOWN:
			case SAMEY_UP:
				box.w = sp.GetWidth();
				if(box.h != sp.GetHeight()){
					box.y += box.h - sp.GetHeight();
					box.h = sp.GetHeight();
				}
				break;
			case DEFAULT:
				if(box.w != sp.GetWidth()){
					box.x += box.w/2 - sp.GetWidth()/2;
					box.w = sp.GetWidth();
				}
				if(box.h != sp.GetHeight()){
					box.y += box.h/2 - sp.GetHeight()/2;
					box.h = sp.GetHeight();
				}
				break;
			default:
				break;
		}

		MovePlayerColliding(w, h);
	}
}

void SceneObject::MovePlayerColliding(float w, float h){
	if(MissionManager::player->box.y + offset < box.y + box.h &&
			!(MissionManager::player->box.y + MissionManager::player->box.h - offset < box.y)){

		if((box.w != w) && (MissionManager::player->GetDirecao() == Player::LESTE ||
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

		if((box.h != h) && (MissionManager::player->GetDirecao() == Player::NORTE ||
			MissionManager::player->GetDirecao() == Player::SUL)){

			if((MissionManager::player->box.y < box.y + box.h &&
					MissionManager::player->box.y + MissionManager::player->box.h > box.y + box.h )
					|| (box.InsideY(MissionManager::player->box) &&
							MissionManager::player->box.CenterY() >= box.CenterY())){
				MissionManager::player->box.y = box.y + box.h + 1;
			} else if((MissionManager::player->box.y + MissionManager::player->box.h > box.y &&
					MissionManager::player->box.y < box.y)
					|| (box.InsideY(MissionManager::player->box) &&
							MissionManager::player->box.CenterY() < box.CenterY())){
				MissionManager::player->box.y = box.y - MissionManager::player->box.h - 1;
			}

		}

	}
}
