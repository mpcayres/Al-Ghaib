#include "Bear.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "MissionManager.hpp"

#define MODULO_SPEED 3
#define AUMENTO_VALUE 2
#define DESACELERA 1

Bear* Bear::bear;
bool Bear::show = false;
bool Bear::seen = false;
bool Bear::arrived = false;
bool Bear::repair = false;

Bear::Bear(float x, float y): sp("img/object-bear-destr.png"){
	//stop = false;
	sp.SetScaleX(2);
	sp.SetScaleY(2);

	//destinationPath.x = x;
	//destinationPath.y = y;

	show = false;

	box.x = x; box.y = y;
	box.w = sp.GetScaledWidth();
	box.h = sp.GetScaledHeight();

	//seen = false;

	time = Timer();

	////direcao = SUL;
	////direcaoShift = false;

	hp = 30;
	rotation = 0;
	speed.y = speed.x = 0;
	bear = this;
}

Bear::~Bear(){
	bear = nullptr;
}

void Bear::Update(float dt){
	Vec2 aux, aux2;

	//float dist = 0;
	if(show){

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
		//if(seen == true) Pursuit();
		/*else*/ DefinedPath();

		/*if(speed.x != 0 || speed.y != 0){
					sp.Update(dt, ////direcao, ////direcaoShift);
		} else{
			if(sp.GetCurrentFrame() > 1 && sp.GetCurrentFrame() < 8){
			if(////direcao == NORTE) speed.y = -DESACELERA;
			if(////direcao == SUL) speed.y = DESACELERA;
			if(////direcao == LESTE) speed.x = DESACELERA;
			if(////direcao == OESTE) speed.x = -DESACELERA;

			sp.Update(dt, ////direcao, ////direcaoShift);
			}
		}*/
	}
}

/*void Bear::Set////direcao(int dir){
	////direcao = (InvBox) dir;
	sp.SetFrame(1, ////direcao);
}*/

void Bear::Render(){
	if(show)
		sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Bear::IsDead(){
	return (hp <= 0);
}


void Bear::Shoot(){
	Vec2 aux;
	aux.x = 70;
	aux.y = 0;
	//aux = aux.Rotate(cannonAngle);
}

bool Bear::NotifyCollision(GameObject& other){
	if(other.Is("CollidableObject")){

		if( MissionManager::player != nullptr){
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
		return MissionManager::player->CollidingPlayer(box, offset);
	}

	if(other.Is("EmptyBox")){
			if(InputManager::GetInstance().KeyPress(Z_KEY) && repair == true){
				sp.Open("img/object-bear.png");

			}
	}

	return false;
}

void Bear::SetDestinationPath(Vec2 path){
	destinationPath.emplace_back(path);
}

void Bear::DefinedPath(){
	Vec2 aux;
		aux.x = box.x; aux.y = box.y;
		//std::cout <<  aux.Distance(destinationPath.back() ) << std::endl;
		if(aux.Distance(destinationPath.back())>2){
		//printf("\n\n %d ; %f - %f", aux.Distance(destinationPath.back())<=10, destinationPath.back().x, destinationPath.back().y);
			if(aux.Distance(destinationPath.back())<= 5 ){
					//printf("POPANDO");

				arrived = true;
				box.x = destinationPath.back().x;
				box.y = destinationPath.back().y;
				destinationPath.pop_back();


			}
			else
				arrived = false;
			//if(destinationPath.empty())
				//show = false;
			if(MissionManager::player != nullptr){
				/*destination.x = MissionManager::player->box.x;
				destination.y = MissionManager::player->box.y;*/
				//seen = true;

				//aux.x = box.x; aux.y = box.y;
				speed = (destinationPath.back().Sub(aux)).Normalize();
				speed.x = speed.x*SPEED_CONTROL;
				speed.y = speed.y*SPEED_CONTROL;
			}

			if(!arrived){
				//std::cout << " DESTINATION PATH "<< (unsigned) (destinationPath.back().x - box.x) << " e " <<  (unsigned) (destinationPath.back().y - box.y) << std::endl;
				if((unsigned) (destinationPath.back().x - box.x) > (unsigned) (destinationPath.back().y - box.y)){
					if(destinationPath.back().x < box.x){
						//std::cout << " OESTE " << std::endl;
						//////direcao = OESTE;
					}else if(destinationPath.back().x > box.x && destinationPath.back().x - box.x < MOV_OFFSET){
						//std::cout << " LESTE " << destinationPath.back().x - box.x << std::endl;
						//////direcao = LESTE;
					}
				}
				else{
						if(destinationPath.back().y < box.y){
						//std::cout << " NORTE " << std::endl;
						//////direcao = NORTE;
					}
					else if(destinationPath.back().y > box.y && destinationPath.back().y -  box.y < MOV_OFFSET){
						//std::cout << " SUL " << std::endl;
						//////direcao = SUL;
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
		}
}

bool Bear::Is(std::string type){
	return (type == "Bear");
}
