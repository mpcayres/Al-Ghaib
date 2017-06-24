#include "MovingObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"
#include "MissionManager.hpp"
#include "Geometry.hpp"

#include <iostream>

MovingObject::MovingObject(float x, float y, std::string img) : sp(img){
	rotation = 0;
	box.x = x; box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	previousPos = Vec2(x,y);
	offset = box.h/3;
}

bool MovingObject::IsDead(){
	return false;
}

void MovingObject::Update(float dt){

}

void MovingObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool MovingObject::NotifyCollision(GameObject& other){
	if(other.Is("EmptyBox")){
		// PODEMOS DIMINUIR A REGIAO ANALISADA DO MOVING OBJECT PARA QUE NAO CONSIGA "PEGAR PELAS PONTAS"
		if(InputManager::GetInstance().IsKeyDown(LCTRL_KEY) && InputManager::GetInstance().KeyPress(C_KEY)){
			//colocar animacao para subir na cadeira
			if(!MissionManager::player->GetAboveObject()){

				MissionManager::player->climbing = true;
				if(MissionManager::player->box.x > box.x){
					MissionManager::player->box.x = MissionManager::player->box.x - MissionManager::player->box.w/2 - 12;
					MissionManager::player->box.y = box.y + box.h/2 - MissionManager::player->box.h/2 - 12;
				}else{
					MissionManager::player->box.x = box.x - MissionManager::player->box.w/2 - 8;
					MissionManager::player->box.y = box.y + box.h/2 - MissionManager::player->box.h/2 - 12;
				}

				MissionManager::player->ChangeAboveObject();

				return true;
			} else{
				//MissionManager::player->climbing = true;
				MissionManager::player->box.x = MissionManager::player->previousPos.x;
				MissionManager::player->box.y = MissionManager::player->previousPos.y;
				MissionManager::player->ChangeAboveObject();
				return false;
			}
		} else if(InputManager::GetInstance().IsKeyDown(C_KEY) && !MissionManager::player->GetAboveObject()){
			MissionManager::missionManager->movingBox = false;
			Rect aux = MissionManager::player->box;
			aux.x += 2; aux.y += 2; aux.w -= 2; aux.h -= 2;
			if(aux.Intersect(box) && (MissionManager::player->GetDirecao() == Player::LESTE ||
					MissionManager::player->GetDirecao() == Player::OESTE)){
				box.x = previousPos.x; box.y = previousPos.y;
				//MissionManager::missionManager->movingBox = true;
				//std::cout << "INTERSECT 1" << std::endl;
			} else if(MissionManager::player->box.Intersect(box) &&
					MissionManager::player->box.x == MissionManager::player->previousPos.x &&
					MissionManager::player->box.y == MissionManager::player->previousPos.y &&
					MissionManager::player->GetDirecao() == Player::SUL &&
					MissionManager::player->GetSpeed().y < 0 &&
					MissionManager::player->box.y + MissionManager::player->box.h - offset < box.y){
				box.x = previousPos.x; box.y = previousPos.y;
				//std::cout << "INTERSECT 2 " << MissionManager::player->GetSpeed().y << std::endl;
			} else if(MissionManager::player->box.Intersect(box) &&
					MissionManager::player->box.x == MissionManager::player->previousPos.x &&
					MissionManager::player->box.y == MissionManager::player->previousPos.y &&
					MissionManager::player->GetDirecao() == Player::NORTE &&
					MissionManager::player->GetSpeed().y > 0 &&
					MissionManager::player->box.y + offset < box.y + box.h){
				box.x = previousPos.x; box.y = previousPos.y;
				//std::cout << "INTERSECT 3 " << MissionManager::player->GetSpeed().y << std::endl;
			} else if(!( (MissionManager::player->GetDirecao() == Player::NORTE &&
							MissionManager::player->GetSpeed().y < 0 &&
							MissionManager::player->box.y + MissionManager::player->box.h - offset < box.y) ||
						(MissionManager::player->GetDirecao() == Player::SUL &&
							MissionManager::player->GetSpeed().y > 0 &&
							MissionManager::player->box.y + offset > box.y + box.h) )){

				MissionManager::missionManager->movingBox = true;
				previousPos = Vec2(box.x, box.y);

				bool bloqMov = false;
				Rect boxAux = box, boxAuxPlayer = MissionManager::player->box;
				boxAux.x += MissionManager::player->GetSpeed().x; boxAux.y += MissionManager::player->GetSpeed().y;
				boxAuxPlayer.x += MissionManager::player->GetSpeed().x; boxAuxPlayer.y += MissionManager::player->GetSpeed().y;
				for(unsigned int i = 0; i < MissionManager::player->wallLimits.size(); i++){
					bloqMov = boxAux.Collide(MissionManager::player->wallLimits[i]);
					if(bloqMov == true) break;
					// talvez nao precise mais desta
					bloqMov = boxAuxPlayer.Collide(MissionManager::player->wallLimits[i]);
					if(bloqMov == true) break;
				}

				if(boxAux.x < MissionManager::player->limits.w - boxAux.w &&
						boxAuxPlayer.x < MissionManager::player->limits.w - boxAuxPlayer.w &&
						boxAux.x > MissionManager::player->limits.x &&
						boxAuxPlayer.x > MissionManager::player->limits.x && !bloqMov){
					if(MissionManager::player->GetDirecao() == Player::LESTE ||
							MissionManager::player->GetDirecao() == Player::OESTE){
						box.x += MissionManager::player->GetSpeed().x;
					}
				}
				if(boxAux.y < MissionManager::player->limits.h - boxAux.h &&
						boxAuxPlayer.y < MissionManager::player->limits.h - boxAuxPlayer.h &&
						boxAux.y > MissionManager::player->limits.y &&
						boxAuxPlayer.y > MissionManager::player->limits.y && !bloqMov){
					if(MissionManager::player->GetDirecao() == Player::NORTE ||
							MissionManager::player->GetDirecao() == Player::SUL){
						box.y += MissionManager::player->GetSpeed().y;
					}
				}
			}
		}
	}

	if(other.Is("Player")){
		return MissionManager::player->CollidingPlayer(box, offset);
	}

	if(other.Is("CollidableObject")){
		box.x = previousPos.x;
		box.y = previousPos.y;
		if(MissionManager::player->box.x < box.x + box.w ||
				MissionManager::player->box.x + MissionManager::player->box.w > box.x){
			MissionManager::player->box.x = MissionManager::player->previousPos.x;
		}
		if(MissionManager::player->box.y < box.y + box.h ||
				MissionManager::player->box.y + MissionManager::player->box.h > box.y){
			MissionManager::player->box.y = MissionManager::player->previousPos.y;
		}
	}

	if (other.Is("Enemy")){
		/*if(other.box.x < box.x + box.w ||
				other.box.x + other.box.w > box.x){
			other.box.x = box.x + box.w + 1;
		} else if(other.box.y < box.y + box.h ||
				other.box.y + other.box.h > box.y){
			other.box.x = box.x - other.box.w - 1;
		}*/

		if((other.box.y + other.box.h - offset < box.y + box.h)){
			if((other.box.x < box.x + box.w &&other.box.x + other.box.w > box.x + box.w )
				|| (box.InsideX(other.box) && other.box.CenterX() >= box.CenterX())){

				if(other.direcao == 3|| other.direcao == 4 ){
					other.box.x = other.previousPos.x;
					other.box.y = other.previousPos.y;
				} else{
					other.box.x = box.x + box.w + 1;
				}
			} else if((other.box.x + other.box.w > box.x && other.box.x < box.x)
				|| (box.InsideX(other.box) && other.box.CenterX() < box.CenterX())){

				if(other.direcao == 3 || other.direcao == 4 ){
					other.box.x = other.previousPos.x;
					other.box.y = other.previousPos.y;
				} else{
					other.box.x = box.x - other.box.w - 1;
				}
			}
		}
	}

	return false;
}

bool MovingObject::Is(std::string type){
	return (type == "MovingObject" || type == "CollidableObject");
}
