#include "InventoryBear.hpp"

InventoryBear::InventoryBear(std::string file) : InventoryObject(file) { }

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
