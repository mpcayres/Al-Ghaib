#include "InventoryWool.hpp"
#include "MissionManager.hpp"
#include "Bear.hpp"

InventoryWool::InventoryWool() : InventoryObject("img/inventario/novelo.png") {
	timesPressed = 0;
}

InventoryWool::~InventoryWool(){ }

bool InventoryWool::Action(GameObject* other){
	if(Bear::bear->colliding){
		timesPressed++;
		MissionManager::player->AddRuido(0.2*50);
		if(timesPressed >= 20){
			Bear::bear->hasCostura = true;
		}
		return true;
	}
	return false;
}

bool InventoryWool::IsObject(std::string type){
	return (type == "InventoryWool" || type == "InventoryMiniGame");
}

std::string InventoryWool::GetObject(){
	return "InventoryWool";
}
