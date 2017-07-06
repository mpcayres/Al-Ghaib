#include "InventoryBook.hpp"
#include "MissionManager.hpp"

InventoryBook::InventoryBook() : InventoryObject("img/cenario/geral/livro.png") {
	timesPressed = 0;
}

InventoryBook::~InventoryBook(){ }

bool InventoryBook::Action(GameObject* other){
	/*if(Bear::bear->colliding){
		timesPressed++;
		MissionManager::player->AddRuido(0.2*50);
		if(timesPressed >= 20){
			Bear::bear->hasCostura = true;
		}
		return true;
	}*/
	return false;
}

bool InventoryBook::IsObject(std::string type){
	return (type == "InventoryBook" || type == "InventoryMiniGame");
}

std::string InventoryBook::GetObject(){
	return "InventoryBook";
}
