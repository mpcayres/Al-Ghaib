/*
 * Minion.cpp
 *
 *  Created on: 2 de abr de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#include "Minion.hpp"
#include "Geometry.hpp"
#include "Camera.hpp"
#include "Bullet.hpp"
#include "Game.hpp"

Minion::Minion(GameObject* minionCenter, float arcOffset){
	Vec2 pos;
	float escala;
	dead = false;

	pos.x = 100;
	pos.y = 0;

	center = minionCenter;
	arc = arcOffset;
	sp.Open("img/minion.png");

	escala = rand()%50;
	escala = (escala/100) +1;
	sp.SetScaleX(escala); sp.SetScaleY(escala);


}

void Minion::Update(float dt){
	float velocidade = dt;
	Vec2 pos, aux, aux2;
	pos.x = 150;
	pos.y = 0;

	pos = pos.Rotate(arc);
	arc -= velocidade;

	box.x = center->box.x - pos.x + sp.GetWidth()/2;
	box.y = center->box.y - pos.y + sp.GetHeight()/2;

	aux.x = box.x; aux2.x = center->box.x;
	aux.y = box.y; aux2.y = center->box.y;


	rotation = aux.Inclination(aux2);
}

void Minion::Shoot(Vec2 pos){
	float angulo;
	Vec2 aux;
	aux.x = box.x+sp.GetWidth()/2;
	aux.y = box.y+sp.GetHeight()/2;
	angulo = (pos.Sub(aux)).Angle();

	Game::GetInstance().GetCurrentState().AddObject(new Bullet(aux.x,aux.y
			,angulo,300,500,"img/minionbullet2.png", 3, 0.2, false));
}

void Minion::Render(){
	sp.Render(box.x + Camera::pos.x,box.y + Camera::pos.y, rotation * 58);
}

bool Minion::IsDead(){
	return dead;
}

void Minion::NotifyCollision(GameObject& other){
	if(other.Is("Bullet")){
		dead = true;
	}
}

bool Minion::Is(std::string type){
	if(type == "Minion") return true;
	else return false;
}




