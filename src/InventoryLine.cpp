#include "InventoryLine.hpp"
#include "MissionManager.hpp"
#include "Bear.hpp"

InventoryLine::InventoryLine() : InventoryObject("img/inventario/carretel.png") {
	timesPressed = 0;
}

InventoryLine::~InventoryLine(){ }

bool InventoryLine::Action(GameObject* other){
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

bool InventoryLine::IsObject(std::string type){
	return (type == "InventoryLine" || type == "InventoryMiniGame");
}

std::string InventoryLine::GetObject(){
	return "InventoryLine";
}
