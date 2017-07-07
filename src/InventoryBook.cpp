#include "InventoryBook.hpp"
#include "MissionManager.hpp"

InventoryBook::InventoryBook() : InventoryObject("img/inventario/livro-simbolo.png") {
	timesPressed = 0;
}

InventoryBook::~InventoryBook(){ }

bool InventoryBook::Action(GameObject* other){
	timesPressed++;
	MissionManager::player->AddRuido(0.2*50);
	if(timesPressed >= 30) return true;
	return false;
}

bool InventoryBook::IsObject(std::string type){
	return (type == "InventoryBook" || type == "InventoryMiniGame");
}

std::string InventoryBook::GetObject(){
	return "InventoryBook";
}
