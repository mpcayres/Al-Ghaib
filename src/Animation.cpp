/*
 * Animation.cpp
 *
 *  Created on: 9 de mai de 2017
 *      Author: renne
 *
 *
 * Aluno: Renne Ruan Alves Oliveira
 * Matricula: 14/0030930
 * Introducao ao Desenvolvimento de Jogos 1/2017
 */

#include "Animation.hpp"
#include "Camera.hpp"

Animation::Animation(float x, float y, float rotation, std::string sprite,
		int frameCount, float frameTime, bool ends){
	sp = Sprite(sprite, frameCount, frameTime);
	box.x = x;
	box.y = y;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
	timeLimit = frameCount*frameTime;
	oneTimeOnly = ends;
	endTimer = Timer();
	this->rotation = rotation;
}

void Animation::Update(float dt){
	endTimer.Update(dt);
	sp.Update(dt);
}

void Animation::Render(){
	sp.Render(box.x + - (box.w/2) + Camera::pos.x, box.y - (box.h/2) + Camera::pos.y, rotation *58);
}

bool Animation::IsDead(){
	if(oneTimeOnly && endTimer.Get()>= timeLimit){
		return true;
	}
	return false;
}

void Animation::NotifyCollision(GameObject& other){}

bool Animation::Is(std::string type){
	return(type == "Animation");
}





