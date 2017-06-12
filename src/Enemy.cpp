#include "Enemy.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "MissionManager.hpp"

#define MODULO_SPEED 3
#define AUMENTO_VALUE 2

Enemy* Enemy::enemy;
bool Enemy::show = false;
bool Enemy::arrived = false;

Enemy::Enemy(float x, float y): sp("img/m2.png"){

	sp.SetScaleX(0.2);
	sp.SetScaleY(0.2);

	//destinationPath.x = x;
	//destinationPath.y = y;

	show = false;

	box.x = x; box.y = y;
	box.w = sp.GetScaledWidth();
	box.h = sp.GetScaledHeight();

	seen = false;

	time = Timer();

	hp = 30;
	rotation = 0;
	speed.y = speed.x = 0;
	enemy = this;
}

Enemy::~Enemy(){
	enemy = nullptr;
}

void Enemy::Update(float dt){
	Vec2 aux, aux2;

	float dist = 0;
	if(show){
		dist = box.DistanceRect(MissionManager::player->box);
		if(dist < 200){
			seen = true;
		}
		float noise = ((100/dist))*MissionManager::player->GetRuido();
		//printf("N: %f\n", noise);
		if(noise >= 15){
			seen = true;
		}

		bool bloqMov = false;
		Rect boxAux = box;
		boxAux.x += speed.x; boxAux.y += speed.y;
		for(unsigned int i = 0; i < MissionManager::player->wallLimits.size(); i++){
			bloqMov = boxAux.Collide(MissionManager::player->wallLimits[i]);
			if(bloqMov == true) break;
		}

		if(boxAux.x < MissionManager::player->limits.w - box.w &&
				boxAux.x > MissionManager::player->limits.x && !bloqMov){
			previousPos.x = box.x;
			box.x += speed.x;
		}
		if(boxAux.y < MissionManager::player->limits.h - box.h &&
				boxAux.y > MissionManager::player->limits.y && !bloqMov){
			previousPos.y = box.y;
			box.y += speed.y;
		}

		if(seen == true) Pursuit();
		if(seen == false) {
			//printf("amigo estou aqui!");
			DefinedPath();
		}
	}
}

void Enemy::Render(){
	if(show)
		sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Enemy::IsDead(){
	return (hp <= 0);
}


void Enemy::Shoot(){
	Vec2 aux;
	aux.x = 70;
	aux.y = 0;
	//aux = aux.Rotate(cannonAngle);
}

void Enemy::NotifyCollision(GameObject& other){
	if(other.Is("CollidableObject")){

		if(seen && MissionManager::player != nullptr){
			//if(MissionManager::player != nullptr){
			Vec2 aux;
			destination.x = MissionManager::player->box.x;
			destination.y = MissionManager::player->box.y;
			//seen = true;

			aux.x = box.x; aux.y = box.y;
			speed = (destination.Sub(aux)).Normalize();
			speed.x = speed.x*SPEED_CONTROL;
			speed.y = speed.y*SPEED_CONTROL;
				//}
		}
	}
	if(other.Is("Player")){
		seen = false;
	}

}
void Enemy::SetDestinationPath(Vec2 path){
	destinationPath.emplace_back(path);
}

void Enemy::DefinedPath(){
	Vec2 aux;
	aux.x = box.x; aux.y = box.y;
	//printf("\n\n %d ; %f - %f", aux.Distance(destinationPath.back())<=10, destinationPath.back().x, destinationPath.back().y);
		if(/*this->box.x == destinationPath.back().x && this->box.y == destinationPath.back().y */ aux.Distance(destinationPath.back())<= 10 ){
				//printf("POPANDO");

			arrived = true;
			destinationPath.pop_back();
		}
		else
			arrived = false;
		if(destinationPath.empty())
			show = false;
		if(MissionManager::player != nullptr){
			/*destination.x = MissionManager::player->box.x;
			destination.y = MissionManager::player->box.y;*/
			//seen = true;

			//aux.x = box.x; aux.y = box.y;
			speed = (destinationPath.back().Sub(aux)).Normalize();
			speed.x = speed.x*SPEED_CONTROL;
			speed.y = speed.y*SPEED_CONTROL;
		}

		if (speed.x < 0 && speed.y < 0){
			if(box.x + speed.x -  VALUE <= destinationPath.back().x  &&
				speed.y + box.y -  VALUE <= destinationPath.back().y){
				box.x = destinationPath.back().x - box.w/2;
				box.y = destinationPath.back().y - box.h/2;

				//seen = false;

			} else{
				box.x += speed.x;
				box.y += speed.y;
			}
		} else if (speed.x > 0 && speed.y < 0){
			if(box.x +speed.x +  VALUE >= destinationPath.back().x &&
					speed.y + box.y -  VALUE <= destinationPath.back().y){
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;

				//seen = false;

				}else{
					box.x += speed.x;
					box.y += speed.y;
				}
		} else if (speed.x < 0 && speed.y > 0){
			if(box.x +speed.x -  VALUE <= destinationPath.back().x &&
					speed.y + box.y +  VALUE >= destinationPath.back().y){
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;

				//seen = false;

				}else{
					box.x += speed.x;
					box.y += speed.y;
				}
		} else if (speed.x > 0 && speed.y > 0){
			if(box.x +speed.x + VALUE >= destinationPath.back().x &&
					speed.y + box.y + VALUE >= destinationPath.back().y){
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;

				//seen = false;
			} else{
				box.x += speed.x;
				box.y += speed.y;
			}
		}


}
void Enemy::Pursuit(){
	Vec2 aux;

	if(MissionManager::player != nullptr){
		destination.x = MissionManager::player->box.x;
		destination.y = MissionManager::player->box.y;
		//seen = true;

		aux.x = box.x; aux.y = box.y;
		speed = (destination.Sub(aux)).Normalize();
		speed.x = speed.x*SPEED_CONTROL;
		speed.y = speed.y*SPEED_CONTROL;
	}

	if (speed.x < 0 && speed.y < 0){
		if(box.x + speed.x -  VALUE <= destination.x &&
			speed.y + box.y -  VALUE <= destination.y){
			box.x = destination.x - box.w/2;
			box.y = destination.y - box.h/2;

			//seen = false;

		} else{
			box.x += speed.x;
			box.y += speed.y;
		}
	} else if (speed.x > 0 && speed.y < 0){
		if(box.x +speed.x +  VALUE >= destination.x &&
				speed.y + box.y -  VALUE <= destination.y){
			box.x = destination.x;
			box.y = destination.y;

			//seen = false;

			}else{
				box.x += speed.x;
				box.y += speed.y;
			}
	} else if (speed.x < 0 && speed.y > 0){
		if(box.x +speed.x -  VALUE <= destination.x &&
				speed.y + box.y +  VALUE >= destination.y){
			box.x = destination.x;
			box.y = destination.y;

			//seen = false;

			}else{
				box.x += speed.x;
				box.y += speed.y;
			}
	} else if (speed.x > 0 && speed.y > 0){
		if(box.x +speed.x + VALUE >= destination.x &&
				speed.y + box.y + VALUE >= destination.y){
			box.x = destination.x;
			box.y = destination.y;

			//seen = false;
		} else{
			box.x += speed.x;
			box.y += speed.y;
		}
	}

}

bool Enemy::Is(std::string type){
	return (type == "Enemy");
}
