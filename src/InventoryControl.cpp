#include "InventoryControl.hpp"
#include "Game.hpp"

InventoryControl::InventoryControl() : InventoryObject("img/object-control.png") { }

InventoryControl::~InventoryControl(){ }

bool InventoryControl::Action(GameObject* other){
	int pos = Game::GetInstance().GetCurrentState().GetPositionArray("SceneAnimated");
	if(pos != -1){
		Game::GetInstance().GetCurrentState().AccessAnimated(pos);
	}
	return false;
}

bool InventoryControl::IsObject(std::string type){
	return (type == "InventoryControl");
}

std::string InventoryControl::GetObject(){
	return "InventoryControl";
}
