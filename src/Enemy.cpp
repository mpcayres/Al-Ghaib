#include "Enemy.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "MissionManager.hpp"

#define MODULO_SPEED 8
#define AUMENTO_VALUE 2

Enemy* Enemy::enemy;

Enemy::Enemy(float x, float y): sp("img/m2.png"){

	sp.SetScaleX(0.3);
	sp.SetScaleY(0.3);

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
	dist = box.DistanceRect(MissionManager::player->box);
	if(dist < 300){
		seen = true;
	}
	float noise = ((100/dist))*MissionManager::player->GetRuido();
	//printf("N: %f\n", noise);
	if(noise >= 15){
		seen = true;
	}

	if(box.y + speed.y < 1280 - box.h && box.y + speed.y > 0){
		box.y += speed.y;
	}
	if(box.x + speed.x < 1408 - box.w && box.x + speed.x > 0){
		box.x += speed.x;
	}

	if(seen == true) Pursuit();
}

void Enemy::Render(){
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
	if(other.Is("SceneObject")){

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
