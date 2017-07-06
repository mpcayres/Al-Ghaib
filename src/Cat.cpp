#include "Cat.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Sound.hpp"
#include "MissionManager.hpp"

#define MODULO_SPEED 0.5
#define AUMENTO_VALUE 2
#define DESACELERA 1

Cat::Cat(float x, float y): sp("img/inventario/novelo.png"){
	//stop = false;
	sp.SetScaleX(0.5);
	sp.SetScaleY(0.5);

	//destinationPath.x = x;
	//destinationPath.y = y;

	show = seen = arrived = attractedWool = attractedTV = false;
	box.x = x; box.y = y;
	box.w = sp.GetScaledWidth();
	box.h = sp.GetScaledHeight();

	//seen = false;

	time = Timer();

	////direcao = SUL;
	////direcaoShift = false;

	rotation = 0;
	speed.y = speed.x = 0;
}

Cat::~Cat(){ }

void Cat::Update(float dt){
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

/*void Cat::Set////direcao(int dir){
	////direcao = (InvBox) dir;
	sp.SetFrame(1, ////direcao);
}*/

void Cat::SetPosition(float x, float y){
	box.x = x;
	box.y = y;
}

void Cat::Render(){
	if(show)
		sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool Cat::IsDead(){
	return false;
}


void Cat::Shoot(){
	Vec2 aux;
	aux.x = 70;
	aux.y = 0;
}

bool Cat::NotifyCollision(GameObject& other){
	if(show){
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
			return MissionManager::player->CollidingPlayer(box, 2);
		}

	}

	return false;
}

void Cat::SetDestinationPath(Vec2 path){
	destinationPath.emplace_back(path);
}

void Cat::DefinedPath(){
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

/*void Cat::Pursuit(){
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
	std::cout << aux.Distance(destination) << std::endl;
	if( aux.Distance(destination) > 200 )
		stop = false;
	if( aux.Distance(destination) > 50 && stop == false){
		stop = false;
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
	}else{
		//seen = false;
		stop = true;
	}
}*/

bool Cat::Is(std::string type){
	return (type == "Cat");
}
