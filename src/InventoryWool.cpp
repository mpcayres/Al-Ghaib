#include "InventoryWool.hpp"

InventoryWool::InventoryWool() : InventoryObject("img/obj_novelo.png") { }

InventoryWool::~InventoryWool(){ }

bool InventoryWool::Action(GameObject* other){
	return false;
}

bool InventoryWool::IsObject(std::string type){
	return (type == "InventoryWool");
}

std::string InventoryWool::GetObject(){
	return "InventoryWool";
}
