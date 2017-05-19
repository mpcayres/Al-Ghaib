/*
 * SceneObject.cpp

 *
 *  Created on: May 18, 2017
 *      Author: ingrid
 */

#include "SceneObject.hpp"
#include "Camera.hpp"
#include "InputManager.hpp"

SceneObject::SceneObject(float x, float y, int id, std::string img) : id(id), sp(img){
	//sp.Open(img);
	estado = false;
	rotation = 0;
	box.x = x  - sp.GetWidth()/2;
	box.y = y  - sp.GetHeight()/2;
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

// Talvez colocar pra pegar quando estiver pr�ximo
void SceneObject::NotifyCollision(GameObject& other){
	if(other.Is("EmptyBox")){
		printf("\nBATII");
		Rect box2;
		if(InputManager::GetInstance().KeyPress(Z_KEY)){
			if (estado == true){
				estado = false;
				printf("dasdsa");
				sp.Open("img/closedwindow.png");
				box2.x = box.x;
				box2.y = box.y;
				box2.h = sp.GetHeight();
				box2.w = sp.GetWidth();
				//box.x = box.x + (box.Center().Distance(box2.Center()));
				//box.y = box.y + (box.Center().Distance(box2.Center()));
				//box = box + (box2.Center() - box.Center());
				//printf("\n TO CLOSED WINDOWbox x %f, y %f -- box 2 x %f, y %f", box.Center().x, box.Center().y, box2.Center().x, box2.Center().y);
				box.x = box.x + (box2.Center().x - box.Center().x);
				box.y = box.y + (box2.Center().y - box.Center().y);

				printf("AQUIII");

			}
			else{ //ok
				estado = true;
				sp.Open("img/openwindow.png");
				box2.x = box.x;
				box2.y = box.y;
				box2.h = sp.GetHeight();
				box2.w = sp.GetWidth();
				//printf("\n TO OPEN WINDOW - -box x %f, y %f -- box 2 x %f, y %f", box.Center().x, box.Center().y, box2.Center().x, box2.Center().y);

				box.x = box.x + (box.Center() - box2.Center()).x;
				box.y = box.y + (box.Center() - box2.Center()).y;
			}
			// adicionar ao invent�rio pelo id
			// ver alguma anima��o
		}
	}
}

bool SceneObject::Is(std::string type){
	return (type == "SceneObject");
}
