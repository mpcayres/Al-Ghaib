#include "InventoryKey.hpp"
#include "SceneDoor.hpp"

InventoryKey::InventoryKey(std::string file) : InventoryObject(file) { }

InventoryKey::~InventoryKey(){ }

bool InventoryKey::Action(GameObject* other){
	if(other->Is("SceneDoor")){
		return (((SceneDoor*)other)->ReceiveAction(this));
	}
	return false;
}

bool InventoryKey::IsObject(std::string type){
	return (type == "InventoryKey");
}

std::string InventoryKey::GetObject(){
	return "InventoryKey";
}
