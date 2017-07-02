#include "InventoryNeedle.hpp"
#include "SceneDoor.hpp"

InventoryNeedle::InventoryNeedle() : InventoryObject("img/object-needle.png") { }

InventoryNeedle::~InventoryNeedle(){ }

bool InventoryNeedle::Action(GameObject* other){
	/*if(other->Is("SceneDoor")){
		return (((SceneDoor*)other)->ReceiveAction(this));
	}*/
	return false;
}

bool InventoryNeedle::IsObject(std::string type){
	return (type == "InventoryNeedle");
}

std::string InventoryNeedle::GetObject(){
	return "InventoryNeedle";
}
