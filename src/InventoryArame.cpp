#include "InventoryArame.hpp"

InventoryArame::InventoryArame() : InventoryKey("img/object-arame.png") { }

InventoryArame::~InventoryArame() { }

bool InventoryArame::IsObject(std::string type){
	return (type == "InventoryArame");
}

std::string InventoryArame::GetObject(){
	return "InventoryArame";
}
