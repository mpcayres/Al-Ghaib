#include "Enemy.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"

#define MODULO_SPEED 8
#define AUMENTO_VALUE 2


Enemy* Enemy::enemy;

Enemy::Enemy(float x, float y): sp("img/m2.png"){

	sp.SetScaleX(0.3);
	sp.SetScaleY(0.3);

	box.x = x; box.y = y;
	box.w = sp.GetScaledWidth();
	box.h = sp.GetScaledHeight();

	running = false;
	seen = false;
	ruido = 0;

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
	/* dinamica de percepcao de ruido vindo do jogador*/
	printf("\n Distancia para jogador");

	float dist = 0;
	int running = 1;
	dist = box.DistanceRect(Player::player->box);
	printf("\n%f", dist);

	if(dist < 250){
		/*if(Player::player != nullptr){
			destination.x = Player::player->box.x;
			destination.y = Player::player->box.y;
			seen = true;

			aux.x = box.x; aux.y = box.y;
			speed = (destination.Sub(aux)).Normalize();
			speed.x = speed.x*SPEED_CONTROL;
			speed.y = speed.y*SPEED_CONTROL;
		}*/
		seen = true;
	}

	printf("\nQuantidade de percepção de ruído acrescentada:");
	if(Player::player->getRunning() == true)
		running = 10;
	else if(!InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY) && !InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY) &&
			!InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY) && !InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)){
		running = 0;
	}
	else
		running = 1;
	float noise = ((1/dist)*10)*running;
	printf("\n%f", noise);
	if(ruido >= 20){
		seen = true;
	}
	ruido += noise;
	printf("\n%f", ruido);


	if(box.y + speed.y < 1280 - box.h && box.y + speed.y > 0){
		box.y += speed.y;
	}
	if(box.x + speed.x < 1408 - box.w && box.x + speed.x > 0){
		box.x += speed.x;
	}
	


	time.Update(dt);


		if(!seen){

		}
		if(seen){
			Pursuit();
		}
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

			if(seen && Player::player != nullptr){
				//if(Player::player != nullptr){
				Vec2 aux;
				destination.x = Player::player->box.x;
				destination.y = Player::player->box.y;
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

	if(Player::player != nullptr){
				destination.x = Player::player->box.x;
				destination.y = Player::player->box.y;
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

		}else{
			box.x += speed.x;
			box.y += speed.y;
		}
	}else if (speed.x > 0 && speed.y < 0){
		if(box.x +speed.x +  VALUE >= destination.x &&
				speed.y + box.y -  VALUE <= destination.y){
			box.x = destination.x;
			box.y = destination.y;

			//seen = false;

			}else{
				box.x += speed.x;
				box.y += speed.y;
			}
	}else if (speed.x < 0 && speed.y > 0){
		if(box.x +speed.x -  VALUE <= destination.x &&
				speed.y + box.y +  VALUE >= destination.y){
			box.x = destination.x;
			box.y = destination.y;

			//seen = false;

			}else{
				box.x += speed.x;
				box.y += speed.y;
			}
	}else if (speed.x > 0 && speed.y > 0){
		if(box.x +speed.x +  VALUE >= destination.x &&
				speed.y + box.y + VALUE >= destination.y){
			box.x = destination.x;
			box.y = destination.y;

			//seen = false;
			}else{
				box.x += speed.x;
				box.y += speed.y;
			}
	}

}

bool Enemy::Is(std::string type){
	return (type == "Enemy");
}
