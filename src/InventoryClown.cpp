#include "InventoryClown.hpp"

InventoryClown::InventoryClown() : InventoryMiniGame("img/object-caixa-sem-palhaco.png",
		"img/object-palhaco-caixa.png", "img/object-palhaco-quebrado.png"){
}

InventoryClown::~InventoryClown() { }

bool InventoryClown::IsObject(std::string type){
	return (type == "InventoryClown" || type == "InventoryMiniGame");
}

std::string InventoryClown::GetObject(){
	return "InventoryClown";
}
