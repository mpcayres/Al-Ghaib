#include "InventoryLine.hpp"
#include "SceneDoor.hpp"

InventoryLine::InventoryLine() : InventoryObject("img/object-needle.png") { }

InventoryLine::~InventoryLine(){ }

bool InventoryLine::Action(GameObject* other){
	/*if(other->Is("SceneDoor")){
		return (((SceneDoor*)other)->ReceiveAction(this));
	}*/
	return false;
}

bool InventoryLine::IsObject(std::string type){
	return (type == "InventoryLine");
}

std::string InventoryLine::GetObject(){
	return "InventoryLine";
}
