/*
 * Alien.cpp
 *
 *  Created on: 2 de abr de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#include "Alien.hpp"
#include "InputManager.hpp"
#include "Game.hpp"
#include "Animation.hpp"
#include "Penguins.hpp"
#include "Bullet.hpp"
#include "Sound.hpp"

int Alien::alienCount;
Alien::Alien(float x,float y, int nMinions){
	sp.Open("img/alien.png");
	Alien::alienCount++;
	box.x = x - sp.GetWidth()/2;
	box.y = y - sp.GetHeight()/2;
	box.h = sp.GetHeight();
	box.w = sp.GetWidth();

	actionDelay = 2+ rand()%8;

	speed.x = 0;
	speed.y = 0;

	hp = 50;

	float delta;
	delta = (2*3.14)/nMinions;
	for(int i = 0; i< nMinions; i++){
		minionArray.emplace_back(Minion(this, delta*i));
	}
	rotation = 0;
	state = RESTING;
}

Alien::~Alien(){
	Alien::alienCount--;
}

void Alien::Render(){
	unsigned i;
	sp.Render(box.x + Camera::pos.x,box.y + Camera::pos.y, rotation);

	for(i = 0; i< minionArray.size(); i++){
		minionArray[i].Render();
	}
}

bool Alien::IsDead(){
	if(hp <= 0) return true;
	return false;
}

void Alien::Update(float dt){
	InputManager instance = InputManager::GetInstace();
	Vec2 aux,aux2, auxtiro;
	unsigned i, candidato;
	float distanciaminion = 1000000000;

	for(unsigned i = 0; i< minionArray.size(); i++){
			minionArray[i].Update(dt);
			if(minionArray[i].IsDead() == true){
				minionArray.erase(minionArray.begin()+ i);
			}
	}

	rotation += 1;

	if(state == RESTING){
		restTimer.Update(dt);

		if(restTimer.Get() >= actionDelay){
			restTimer.Restart();

			if(Penguins::player != nullptr){
				destination.x = Penguins::player->box.x;
				destination.y = Penguins::player->box.y;
				state = MOVING;

				aux.x = box.x; aux.y = box.y;
				speed = (destination.Sub(aux)).Normalize();
				speed.x = speed.x*10;
				speed.y = speed.y*10;
			}
		}
	}
	if(state == MOVING){
		//std::cout << speed.x <<" " << speed.y<<"\n";
		if (speed.x < 0 && speed.y < 0){
			if(box.x + speed.x - 3 <= destination.x &&
				speed.y + box.y - 3 <= destination.y){
				box.x = destination.x - box.w/2;
				box.y = destination.y - box.h/2;

				if(Penguins::player != nullptr){
					aux2.x = Penguins::player->box.x;
					aux2.y = Penguins::player->box.y;
					for(i = 0; i < minionArray.size(); i++){
						auxtiro.x = minionArray[i].box.x;
						auxtiro.y = minionArray[i].box.y;
						if(distanciaminion > auxtiro.Distance(destination)){
							distanciaminion = auxtiro.Distance(destination);
							candidato = i;
						}
					}
					minionArray[candidato].Shoot(aux2);
				}
				state = RESTING;

				restTimer.Restart();

			}else{
				box.x += speed.x;
				box.y += speed.y;
			}
		}else if (speed.x > 0 && speed.y < 0){
			if(box.x +speed.x +3 >= destination.x &&
					speed.y + box.y - 3 <= destination.y){
				box.x = destination.x;
				box.y = destination.y;

				if(Penguins::player != nullptr){
					aux2.x = Penguins::player->box.x;
					aux2.y = Penguins::player->box.y;
					for(i = 0; i < minionArray.size(); i++){
						auxtiro.x = minionArray[i].box.x;
						auxtiro.y = minionArray[i].box.y;
						if(distanciaminion > auxtiro.Distance(destination)){
							distanciaminion = auxtiro.Distance(destination);
							candidato = i;
						}
					}
					minionArray[candidato].Shoot(aux2);
				}
				state = RESTING;

				restTimer.Restart();
				}else{
					box.x += speed.x;
					box.y += speed.y;
				}
		}else if (speed.x < 0 && speed.y > 0){
			if(box.x +speed.x - 3 <= destination.x &&
					speed.y + box.y +3 >= destination.y){
				box.x = destination.x;
				box.y = destination.y;

				if(Penguins::player != nullptr){
					aux2.x = Penguins::player->box.x;
					aux2.y = Penguins::player->box.y;
					for(i = 0; i < minionArray.size(); i++){
						auxtiro.x = minionArray[i].box.x;
						auxtiro.y = minionArray[i].box.y;
						if(distanciaminion > auxtiro.Distance(destination)){
							distanciaminion = auxtiro.Distance(destination);
							candidato = i;
						}
					}
					minionArray[candidato].Shoot(aux2);
				}
				state = RESTING;

				restTimer.Restart();
				}else{
					box.x += speed.x;
					box.y += speed.y;
				}
		}else if (speed.x > 0 && speed.y > 0){
			if(box.x +speed.x + 3 >= destination.x &&
					speed.y + box.y +3 >= destination.y){
				box.x = destination.x;
				box.y = destination.y;

				if(Penguins::player != nullptr){
					aux2.x = Penguins::player->box.x;
					aux2.y = Penguins::player->box.y;
					for(i = 0; i < minionArray.size(); i++){
						auxtiro.x = minionArray[i].box.x;
						auxtiro.y = minionArray[i].box.y;
						if(distanciaminion > auxtiro.Distance(destination)){
							distanciaminion = auxtiro.Distance(destination);
							candidato = i;
						}
					}
					minionArray[candidato].Shoot(aux2);
				}
				state = RESTING;

				restTimer.Restart();
				}else{
					box.x += speed.x;
					box.y += speed.y;
				}
		}
	}
}





void Alien::NotifyCollision(GameObject& other){
	Sound sound = Sound("audio/boom.wav");
	if(other.Is("Bullet")){
		if(!((Bullet&) other).targetsPlayer)
			hp -= 10;
	 }
	if(hp <= 0 ){
		sound.Play(0);
		Game::GetInstance().GetCurrentState().AddObject(
				new Animation(box.Center().x, box.Center().y, rotation
						, "img/aliendeath.png", 4, 0.25, true));

		for(unsigned i = 0; i< minionArray.size(); i++){
				Game::GetInstance().GetCurrentState().AddObject(
						new Animation(minionArray[i].box.Center().x, minionArray[i].box.Center().y,
								minionArray[i].rotation, "img/miniondeath.png", 4, 0.25, true));
		}
	}
}

bool Alien::Is(std::string type){
	if(type == "Alien") return true;
	else return false;
}





