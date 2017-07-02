#include "InventoryBear.hpp"

InventoryBear::InventoryBear() : InventoryObject("img/object-bear.png") { }

InventoryBear::~InventoryBear(){ }

bool InventoryBear::Action(GameObject* other){
	return false;
}

bool InventoryBear::IsObject(std::string type){
	return (type == "InventoryBear");
}

std::string InventoryBear::GetObject(){
	return "InventoryBear";
}
