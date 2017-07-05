#include "InventoryClown.hpp"

InventoryClown::InventoryClown() : InventoryMiniGame("img/inventario/palhaco-dentro-caixa.png",
		"img/inventario/palhaco-caixa.png", "img/inventario/palhaco-quebrado.png"){
}

InventoryClown::~InventoryClown() { }

bool InventoryClown::IsObject(std::string type){
	return (type == "InventoryClown" || type == "InventoryMiniGame");
}

std::string InventoryClown::GetObject(){
	return "InventoryClown";
}
