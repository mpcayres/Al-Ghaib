#include "Walls.hpp"

#include "Geometry.hpp"
#include "Sprite.hpp"
#include "Game.hpp"
#include "Player.hpp"

#include "Camera.hpp"
#include "InputManager.hpp"

Walls::Walls(float x, float y, float w, float h){
	rotation = 0;
	box.x = x;
	box.y = y;
	box.w = w;
	box.h = h;
}
Walls::~Walls(){

}
void Walls::Render(){
	SDL_Rect dst;
	dst.x = box.x - Camera::pos.x; dst.y = box.y - Camera::pos.y;
	dst.h = box.h; dst.w = box.w;
	SDL_RenderDrawRect(Game::GetInstance().GetRenderer(), &dst);
}
void Walls::NotifyCollision(GameObject& other){

	if(other.Is("Player")){
		if(Player::player->box.x < box.x + box.w ||
			Player::player->box.x + Player::player->box.w > box.x){
				Player::player->box.x = Player::player->previousPos.x;
		}
		if(Player::player->box.y < box.y + box.h ||
			Player::player->box.y + Player::player->box.h > box.y){
				Player::player->box.y = Player::player->previousPos.y;
		}
	}


		if (other.Is("Enemy")){
			if(other.box.x < box.x + box.w ||
					other.box.x + other.box.w > box.x){
				other.box.x = box.x + box.w + 1;
			} else if(other.box.y < box.y + box.h ||
					other.box.y + other.box.h > box.y){
				other.box.x = box.x - other.box.w - 1;
			}
		}

		if (other.Is("MovingObject")){
			if(other.box.y + other.box.h < box.y + box.h)
								/*&& (Player::player->GetDirecao() == Player::LESTE ||
									Player::player->GetDirecao() == Player::OESTE))*/{

					if((other.box.x < box.x + box.w &&
							other.box.x + other.box.w > box.x + box.w )
							|| (box.InsideX(other.box) &&
							other.box.CenterX() >= box.CenterX())){
										other.box.x = box.x + box.w + 1;
					} else if((other.box.x + other.box.w > box.x &&
							other.box.x < box.x)
							|| (box.InsideX(Player::player->box) &&
							other.box.CenterX() < box.CenterX())){
									other.box.x = box.x - other.box.w - 1;
					}

			}

		}
}
bool Walls::Is(std::string type){
	return (type == "Wall");
}
bool Walls::IsDead(){
	return false;
}
void Walls::Update(float dt){
}

