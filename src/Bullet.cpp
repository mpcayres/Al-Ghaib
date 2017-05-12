/*
 * Bullet.cpp
 *
 *  Created on: 16 de abr de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#include "Bullet.hpp"
#include "Camera.hpp"

Bullet::Bullet(float x, float y, float angle, float speed, float maxDistance,
		std::string sprite, int frames, float frameTime, bool isPlayer){
	sp = Sprite(sprite, frames, frameTime);
	Vec2 aux;
	rotation = angle;
	aux.x = speed;
	aux.y = 0;
	this->speed = aux.Rotate(angle);
	targetsPlayer = !isPlayer;



	box.x = x  - sp.GetWidth()/2;
	box.y = y  - sp.GetHeight()/2;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	distanceLeft = maxDistance;
}

void Bullet::Update(float dt){
	box.x += dt* speed.x;
	box.y += dt* speed.y;

	distanceLeft -= dt * speed.Abs();
	sp.Update(dt);
}

void Bullet::Render(){
	sp.Render(box.x + Camera::pos.x,box.y + Camera::pos.y, rotation * 58);

}

bool Bullet::IsDead(){
	if(distanceLeft <= 0) return true;
	return false;
}

void Bullet::NotifyCollision(GameObject& other){
	if(!other.Is("Bullet")){
		if(targetsPlayer == true && !other.Is("Alien")){
			distanceLeft = 0;
		}
		if(targetsPlayer == false && !other.Is("Penguins")){
			distanceLeft = 0;
		}
	}
}

bool Bullet::Is(std::string type){
	if(type == "Bullet") return true;
	else return false;
}


