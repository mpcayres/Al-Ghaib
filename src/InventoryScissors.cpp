#include "InventoryScissors.hpp"

InventoryScissors::InventoryScissors() : InventoryObject("img/object-scissors.png") { }

InventoryScissors::~InventoryScissors(){ }

bool InventoryScissors::Action(GameObject* other){
	return false;
}

bool InventoryScissors::IsObject(std::string type){
	return (type == "InventoryScissors");
}

std::string InventoryScissors::GetObject(){
	return "InventoryScissors";
}
