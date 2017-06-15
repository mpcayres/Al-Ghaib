#include "InventoryClown.hpp"

InventoryClown::InventoryClown() : InventoryMiniGame("img/key.png"){ }

InventoryClown::~InventoryClown() { }

bool InventoryClown::IsObject(std::string type){
	return (type == "InventoryClown" || type == "InventoryMiniGame");
}

std::string InventoryClown::GetObject(){
	return "InventoryClown";
}
