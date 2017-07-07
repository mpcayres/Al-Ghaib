#include "Enemy.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "MissionManager.hpp"

#define MODULO_SPEED 2
#define AUMENTO_VALUE 2
#define DESACELERA 1

Enemy::Enemy(float x, float y): sp("img/sprite/mom.png", 8, 0.06, 4){

	sp.SetScaleX(2);
	sp.SetScaleY(2);

	box.x = x; box.y = y;
	box.w = sp.GetScaledWidth();
	box.h = sp.GetScaledHeight();

	show = false;
	arrived = false;
	collidingPlayer = false;
	seen = false;
	canPursuit = true;
	inDefinedPath = false;
	bloq = false;

	time = Timer();

	direcao = SUL;

	rotation = 0;
	speed.y = speed.x = 0;
	direcaoShift = false;
}

Enemy::~Enemy(){ }

void Enemy::Update(float dt){
	if(show && !bloq){
		Vec2 aux, aux2;
		float dist = 0;

		dist = box.DistanceRect(MissionManager::player->box);
		float noise = ((100/dist))*MissionManager::player->GetRuido();
		//printf("N: %f\n", noise);
		if((noise >= 15) || ((MissionManager::player->GetRuido()>70) && !inDefinedPath && canPursuit)){
			seen = true;
		}

		box.x += speed.x;
		box.y += speed.y;

		if(destinationPursuit.size()>0 && !inDefinedPath){
			Pursuit();
		}else if(destinationPath.size() > 0){
			DefinedPath();
		}
		else {
			speed.x = 0;
			speed.y = 0;
			sp.SetFrame(1,2);
		}

		if(speed.x != 0 || speed.y != 0){
			sp.Update(dt, direcao, direcaoShift);
		} else{
			if(sp.GetCurrentFrame() > 1 && sp.GetCurrentFrame() < 8){
			if(direcao == NORTE) speed.y = -DESACELERA;
			if(direcao == SUL) speed.y = DESACELERA;
			if(direcao == LESTE) speed.x = DESACELERA;
			if(direcao == OESTE) speed.x = -DESACELERA;

			sp.Update(dt, direcao, direcaoShift);
			}
		}
	}

	collidingPlayer = false;
}

void Enemy::SetPosition(float x, float y){
	box.x = x;
	box.y = y;
}

void Enemy::SetDirecao(int dir){
	direcao = (InvBox) dir;
	sp.SetFrame(1, direcao);
}

void Enemy::Render(){
	if(show)
		sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Enemy::IsDead(){
	return false;
}

bool Enemy::NotifyCollision(GameObject& other){
	if(show && !MissionManager::player->hidden){
		if(other.Is("Player")){
			seen = false;
			collidingPlayer = true;
		}
	}

	return false;
}

void Enemy::SetDestinationPath(Vec2 path){
	destinationPath.emplace_back(path);
}

void Enemy::PathFlush(){
	while(!destinationPath.empty())
		destinationPath.pop_back();
	while(!destinationPursuit.empty())
		destinationPursuit.pop();
	inDefinedPath = false;
	canPursuit = true;
}

void Enemy::DefinedPath(){
	Vec2 aux;
	aux.x = box.x; aux.y = box.y;
	inDefinedPath = true;
	canPursuit = false;


		if( aux.Distance(destinationPath.back())<= 10 ){
			destinationPath.pop_back();
		}

		speed = (destinationPath.back().Sub(aux)).Normalize();
		speed.x = speed.x*SPEED_CONTROL;
		speed.y = speed.y*SPEED_CONTROL;


		if(destinationPath.empty()){
			speed.x = 0;
			speed.y = 0;
			direcao = SUL;
			inDefinedPath = false;
			canPursuit = true;
		}

		if(speed.x > 0 && abs(speed.y) < 5){
			direcao = LESTE;
		}else if (speed.x < 0 && abs(speed.y) < 5){
			direcao = OESTE;
		}else if (abs(speed.x) < 5 && speed.y < 0){
			direcao = NORTE;
		}else{
			direcao = SUL;
		}

		if (speed.x < 0 && speed.y < 0){
			if(box.x + speed.x -  10 <= destinationPath.back().x  &&
				speed.y + box.y -  10 <= destinationPath.back().y){
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;
			} else{
				box.x += speed.x;
				box.y += speed.y;
			}
		} else if (speed.x > 0 && speed.y < 0){
			if(box.x +speed.x +  10 >= destinationPath.back().x &&
					speed.y + box.y - 10 <= destinationPath.back().y){
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;

				}else{
					box.x += speed.x;
					box.y += speed.y;
				}
		} else if (speed.x < 0 && speed.y > 0){
			if(box.x +speed.x - 10 <= destinationPath.back().x &&
					speed.y + box.y +  10 >= destinationPath.back().y){
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;
				}else{
					box.x += speed.x;
					box.y += speed.y;
				}
		} else if (speed.x > 0 && speed.y > 0){
			if(box.x +speed.x + 10 >= destinationPath.back().x &&
					speed.y + box.y + 10 >= destinationPath.back().y){
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;
			} else{
				box.x += speed.x;
				box.y += speed.y;
			}
		}

}

void Enemy::SetDestinationPursuit(std::queue<Vec2> path){
	std::queue<Vec2> aux = path;
	canPursuit = false;
	for(unsigned i = 0; i < path.size(); i++){
		destinationPursuit.emplace(Vec2(aux.front().x, aux.front().y - sp.GetHeight()-30));
		aux.pop();
	}
}
void Enemy::Reset(){
	while(!destinationPath.empty()){
			destinationPath.pop_back();
	}
}

void Enemy::Pursuit(){
	Vec2 aux;
	aux.x = box.x; aux.y = box.y;

		if( aux.Distance(destinationPursuit.front())<= 10 ){
			destinationPursuit.pop();
		}

		speed = (destinationPursuit.front().Sub(aux)).Normalize();
		speed.x = speed.x*SPEED_CONTROL;
		speed.y = speed.y*SPEED_CONTROL;

		if(destinationPursuit.empty()){
			speed.x = 0;
			speed.y = 0;
			direcao = SUL;
			canPursuit = true;
		}

		if(speed.x > 0 && abs(speed.y) < 5){
			direcao = LESTE;
		}else if (speed.x < 0 && abs(speed.y) < 5){
			direcao = OESTE;
		}else if (abs(speed.x) < 5 && speed.y < 0){
			direcao = NORTE;
		}else{
			direcao = SUL;
		}

		if (speed.x < 0 && speed.y < 0){
			if(box.x + speed.x -  10 <= destinationPursuit.front().x  &&
				speed.y + box.y -  10 <= destinationPursuit.front().y){
				box.x = destinationPursuit.front().x ;
				box.y = destinationPursuit.front().y ;

			} else{
				box.x += speed.x;
				box.y += speed.y;
			}
		} else if (speed.x > 0 && speed.y < 0){
			if(box.x +speed.x +  10 >= destinationPursuit.front().x &&
					speed.y + box.y -  10 <= destinationPursuit.front().y){
				box.x = destinationPursuit.front().x;
				box.y = destinationPursuit.front().y;
				}else{
					box.x += speed.x;
					box.y += speed.y;
				}
		} else if (speed.x < 0 && speed.y > 0){
			if(box.x +speed.x -  10 <= destinationPursuit.front().x &&
					speed.y + box.y +  10 >= destinationPursuit.front().y){
				box.x = destinationPursuit.front().x;
				box.y = destinationPursuit.front().y;
				}else{
					box.x += speed.x;
					box.y += speed.y;
				}
		} else if (speed.x > 0 && speed.y > 0){
			if(box.x +speed.x + 10 >= destinationPursuit.front().x &&
					speed.y + box.y + 10 >= destinationPursuit.front().y){
				box.x = destinationPursuit.front().x;
				box.y = destinationPursuit.front().y;
			} else{
				box.x += speed.x;
				box.y += speed.y;
			}
		}

}

bool Enemy::Is(std::string type){
	return (type == "Enemy");
}

void Enemy::SetDead(){
	Game::GetInstance().GetCurrentState().RemoveEnemy();
}

void Enemy::ChangeClothes(int num){
	switch(num){
	case 1:
		sp = Sprite("img/sprite/mom-chador.png", 8, 0.06, 4);
		sp.SetScaleX(2);
		sp.SetScaleY(2);
		//box.x = box.x; box.y = box.y;
		box.w = sp.GetScaledWidth();
		box.h = sp.GetScaledHeight();
		break;
	case 2:
		sp = Sprite("img/sprite/mom-djinn.png", 8, 0.06, 4);
		sp.SetScaleX(2);
		sp.SetScaleY(2);
		//box.x = box.x; box.y = box.y;
		box.w = sp.GetScaledWidth();
		box.h = sp.GetScaledHeight();
		break;
	}
}

int Enemy::GetHeight(){
	return sp.GetHeight();
}
int Enemy::GetWidth(){
	return sp.GetWidth();
}

