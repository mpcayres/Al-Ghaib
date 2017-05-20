/*
 * SceneObject.cpp

 *
 *  Created on: May 18, 2017
 *      Author: ingrid
 */

#include "SceneObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"

//Foi implementada como a janela, talvez a classe tenha filhos
//Mas do jeito que está pode ser reaproveitada com imagens diferentes
SceneObject::SceneObject(float x, float y, int id, std::string img) :
	id(id), sp(img){
	estado = false;
	rotation = 0;
	box.x = x - sp.GetWidth()/2;
	box.y = y - sp.GetHeight()/2;
	box.w = sp.GetWidth();
	box.h = sp.GetHeight();
}

bool SceneObject::IsDead(){
	return false;
}

void SceneObject::Update(float dt){

}

void SceneObject::Render(){
	sp.Render(box.x - Camera::pos.x, box.y - Camera::pos.y, rotation);
}

bool SceneObject::IsEstado(){
	return estado;
}

void SceneObject::NotifyCollision(GameObject& other){
	//printf("\num fora");
	if(other.Is("EmptyBox")){
		//printf("\nBATII");
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			if(estado){
				estado = false;
				sp.Open("img/closedwindow.png");
				box.x = box.x + box.w/2 - sp.GetWidth()/2;
				box.y = box.y + box.h/2 - sp.GetHeight()/2;
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();
			} else{ //ok
				estado = true;
				sp.Open("img/openwindow.png");
				box.x = box.x + box.w/2 - sp.GetWidth()/2;
				box.y = box.y + box.h/2 - sp.GetHeight()/2;
				box.w = sp.GetWidth();
				box.h = sp.GetHeight();
			}
		}
	}
}

bool SceneObject::Is(std::string type){
	return (type == "SceneObject");
}
