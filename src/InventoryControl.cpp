#include "InventoryControl.hpp"

InventoryControl::InventoryControl() : InventoryObject("img/object-control.png") { }

InventoryControl::~InventoryControl(){ }

bool InventoryControl::Action(GameObject* other){

	return false;
}

bool InventoryControl::IsObject(std::string type){
	return (type == "InventoryControl");
}

std::string InventoryControl::GetObject(){
	return "InventoryControl";
}
