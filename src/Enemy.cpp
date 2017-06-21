#include "Enemy.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "MissionManager.hpp"

#define MODULO_SPEED 3
#define AUMENTO_VALUE 2
#define DESACELERA 1

Enemy* Enemy::enemy;
bool Enemy::show;
bool Enemy::arrived;
bool Enemy::collidingPlayer;
bool Enemy::dead;

Enemy::Enemy(float x, float y): sp("img/sprite-mom.png", 8, 0.06, 4){

	sp.SetScaleX(2);
	sp.SetScaleY(2);

	//destinationPath.x = x;
	//destinationPath.y = y;

	box.x = x; box.y = y;
	box.w = sp.GetScaledWidth();
	box.h = sp.GetScaledHeight();

	show = false;
	arrived = false;
	collidingPlayer = false;
	dead = false;
	seen = false;

	time = Timer();

	direcao = SUL;

	rotation = 0;
	speed.y = speed.x = 0;
	enemy = this;
	direcaoShift = false;
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
		if(noise >= 15 || MissionManager::player->GetRuido()>70){
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
				boxAux.x > MissionManager::player->limits.x - sp.GetWidth() *2&& !bloqMov){
			previousPos.x = box.x;
			box.x += speed.x;
		}
		if(boxAux.y < MissionManager::player->limits.h - box.h &&
				boxAux.y > MissionManager::player->limits.y - sp.GetHeight() *2&& !bloqMov){
			previousPos.y = box.y;
			box.y += speed.y;
		}
		direcao = LESTE;
		if(seen == true) Pursuit();
		if(seen == false)DefinedPath();

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

void Enemy::SetDirecao(int dir){
	direcao = (InvBox) dir;
	sp.SetFrame(1, direcao);
}

void Enemy::Render(){
	if(show)
		sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Enemy::IsDead(){
	return dead;
}


void Enemy::Shoot(){
	Vec2 aux;
	aux.x = 70;
	aux.y = 0;
	//aux = aux.Rotate(cannonAngle);
}

bool Enemy::NotifyCollision(GameObject& other){
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
		collidingPlayer = true;
	}

	return false;
}

void Enemy::SetDestinationPath(Vec2 path){
	destinationPath.emplace_back(path);
}

void Enemy::DefinedPath(){
	Vec2 aux;
	aux.x = box.x; aux.y = box.y;
	//printf("\n\n %d ; %f - %f", aux.Distance(destinationPath.back())<=10, destinationPath.back().x, destinationPath.back().y);
		if(/*this->box.x == destinationPath.back().x && this->box.y == destinationPath.back().y */ aux.Distance(destinationPath.back())<= 5 ){
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

		//if(arrived){
			//std::cout << " DESTINATION PATH "<< (unsigned) (destinationPath.back().x - box.x) << " e " <<  (unsigned) (destinationPath.back().y - box.y) << std::endl;
			if((unsigned) (destinationPath.back().x - box.x) > (unsigned) (destinationPath.back().y - box.y)){
				if(destinationPath.back().x < box.x){
					//std::cout << " OESTE " << std::endl;
					direcao = OESTE;
				} else if(destinationPath.back().x > box.x && destinationPath.back().x - box.x < MOV_OFFSET){
					//std::cout << " LESTE " << destinationPath.back().x - box.x << std::endl;
					direcao = LESTE;
				}
			}
			else{
					if(destinationPath.back().y < box.y){
					//std::cout << " NORTE " << std::endl;
					direcao = NORTE;
				}
				else if(destinationPath.back().y > box.y && destinationPath.back().y -  box.y < MOV_OFFSET){
					//std::cout << " SUL " << std::endl;
					direcao = SUL;
				}
			}
		//}

		if (speed.x < 0 && speed.y < 0){
			if(box.x + speed.x -  VALUE <= destinationPath.back().x  &&
				speed.y + box.y -  VALUE <= destinationPath.back().y){
				previousPos.x = box.x;
				previousPos.y = box.y;
				box.x = destinationPath.back().x - box.w/2;
				box.y = destinationPath.back().y - box.h/2;

				//seen = false;

			} else{
				previousPos.x = box.x;
				previousPos.y = box.y;
				box.x += speed.x;
				box.y += speed.y;
			}
		} else if (speed.x > 0 && speed.y < 0){
			if(box.x +speed.x +  VALUE >= destinationPath.back().x &&
					speed.y + box.y -  VALUE <= destinationPath.back().y){
				previousPos.x = box.x;
				previousPos.y = box.y;
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;

				//seen = false;

				}else{
					previousPos.x = box.x;
					previousPos.y = box.y;
					box.x += speed.x;
					box.y += speed.y;
				}
		} else if (speed.x < 0 && speed.y > 0){
			if(box.x +speed.x -  VALUE <= destinationPath.back().x &&
					speed.y + box.y +  VALUE >= destinationPath.back().y){
				previousPos.x = box.x;
				previousPos.y = box.y;
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;

				//seen = false;

				}else{
					previousPos.x = box.x;
					previousPos.y = box.y;
					box.x += speed.x;
					box.y += speed.y;
				}
		} else if (speed.x > 0 && speed.y > 0){
			if(box.x +speed.x + VALUE >= destinationPath.back().x &&
					speed.y + box.y + VALUE >= destinationPath.back().y){
				previousPos.x = box.x;
				previousPos.y = box.y;
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;

				//seen = false;
			} else{
				previousPos.x = box.x;
				previousPos.y = box.y;
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
	if((unsigned) (destination.x- box.x) > (unsigned) (destination.y- box.y)){
		if(destination.x > box.x){
			//std::cout << " lESTE " << std::endl;
					direcao = LESTE;
		}else if(destination.x < box.CenterX() || destination.x < box.x){
			//std::cout << " OESTE " << std::endl;
			direcao = OESTE;
		}
	}
	else{
		if(destination.y > box.y){
			//std::cout << " SUL " << std::endl;
			direcao = SUL;
		}else if(destination.y < box.CenterY()  || destination.y < box.y){
			//std::cout << " NORTE " << std::endl;
			direcao = NORTE;
		}
	}


	if (speed.x < 0 && speed.y < 0){
		if(box.x + speed.x -  VALUE <= destination.x &&
			speed.y + box.y -  VALUE <= destination.y){
			previousPos.x = box.x;
			previousPos.y = box.y;
			box.x = destination.x - box.w/2;
			box.y = destination.y - box.h/2;

			//seen = false;

		} else{
			previousPos.x = box.x;
			previousPos.y = box.y;
			box.x += speed.x;
			box.y += speed.y;
		}
	} else if (speed.x > 0 && speed.y < 0){
		if(box.x +speed.x +  VALUE >= destination.x &&
				speed.y + box.y -  VALUE <= destination.y){
			previousPos.x = box.x;
			previousPos.y = box.y;
			box.x = destination.x;
			box.y = destination.y;

			//seen = false;

			}else{
				previousPos.x = box.x;
				previousPos.y = box.y;
				box.x += speed.x;
				box.y += speed.y;
			}
	} else if (speed.x < 0 && speed.y > 0){
		if(box.x +speed.x -  VALUE <= destination.x &&
				speed.y + box.y +  VALUE >= destination.y){
			previousPos.x = box.x;
			previousPos.y = box.y;
			box.x = destination.x;
			box.y = destination.y;

			//seen = false;

			}else{
				previousPos.x = box.x;
				previousPos.y = box.y;
				box.x += speed.x;
				box.y += speed.y;
			}
	} else if (speed.x > 0 && speed.y > 0){
		if(box.x +speed.x + VALUE >= destination.x &&
				speed.y + box.y + VALUE >= destination.y){
			previousPos.x = box.x;
			previousPos.y = box.y;
			box.x = destination.x;
			box.y = destination.y;

			//seen = false;
		} else{
			previousPos.x = box.x;
			previousPos.y = box.y;
			box.x += speed.x;
			box.y += speed.y;
		}
	}

}

bool Enemy::Is(std::string type){
	return (type == "Enemy");
}

void Enemy::SetDead(){
	dead = true;
}
