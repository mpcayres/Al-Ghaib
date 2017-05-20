#include "SceneObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"
#include "Player.hpp"

//Foi implementada como a janela, talvez a classe tenha filhos
//Mas do jeito que esta pode ser reaproveitada com imagens diferentes
SceneObject::SceneObject(float x, float y, int id, std::string img) :
	id(id), sp(img){
	estado = false;
	rotation = 0;
	box.x = x - sp.GetWidth()/2;
	box.y = y - sp.GetHeight()/2;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
}

bool SceneObject::IsDead(){
	return false;
}

void SceneObject::Update(float dt){

}

void SceneObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool SceneObject::IsEstado(){
	return estado;
}

void SceneObject::NotifyCollision(GameObject& other){
	//printf("\num fora");
	if(other.Is("EmptyBox")){
		//printf("\nBATII");
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			if(estado){ //ok
				estado = false;
				sp.Open("img/closedwindow.png");
				box.x = box.x + box.w/2 - sp.GetWidth()/2;
				box.y = box.y + box.h/2 - sp.GetHeight()/2;
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();
			} else{ //ok
				estado = true;
				sp.Open("img/openwindow.png");
				box.x = box.x + box.w/2 - sp.GetWidth()/2;
				box.y = box.y + box.h/2 - sp.GetHeight()/2;
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();
			}
			//Tentando arrumar para quando o objeto aumenta e o player fica preso dentro
			/*if(Player::player->box.x < box.x + box.w){
				Player::player->box.x = box.x + box.w + 1;
			} else if(Player::player->box.x + Player::player->box.w > box.x){
				Player::player->box.x = box.x - 1;
			}
			if(Player::player->box.y < box.y + box.h){
				Player::player->box.y = box.y + box.h + 1;
			} else if(Player::player->box.y + Player::player->box.h > box.y){
				Player::player->box.y = box.y - 1;
			}*/
		}
	}
	if(other.Is("Player")){
		/*if(Player::player->box.CenterX()>box.x){
			Player::player->box.x += Player::player->box.w/2;
		}
		else if(Player::player->box.CenterX()<box.x){
			Player::player->box.x -= Player::player->box.w/2;
		}
		if(Player::player->box.CenterY() < box.y + box.h){
 +			Player::player->box.y = Player::player->previousPos.y;
 +		}
 +		else if(Player::player->box.y + Player::player->box.h < box.y + box.h){
 +			Player::player->box.y = Player::player->previousPos.y;
 +		}*/
		// Coloquei assim e está funcionando o suficiente
		/*if(Player::player->box.x < box.x + box.w ||
				Player::player->box.x + Player::player->box.w > box.x){
			Player::player->box.x = Player::player->previousPos.x;
		}
		if(Player::player->box.y < box.y + box.h ||
				Player::player->box.y + Player::player->box.h > box.y){
			Player::player->box.y = Player::player->previousPos.y;
		}*/
	}
}

bool SceneObject::Is(std::string type){
	return (type == "SceneObject");
}
