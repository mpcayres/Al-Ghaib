#include "InventoryClown.hpp"

InventoryClown::InventoryClown() : InventoryMiniGame("img/object-caixa-sem-palhaco.png",
		"img/object-palhaco-caixa.png", "img/object-palhaco-quebrado.png"){
	sp.SetScaleX(0.5); sp.SetScaleY(0.5);
	sp2.SetScaleX(0.3); sp2.SetScaleY(0.3);
	sp3.SetScaleX(0.5); sp3.SetScaleY(0.5);
}

InventoryClown::~InventoryClown() { }

bool InventoryClown::IsObject(std::string type){
	return (type == "InventoryClown" || type == "InventoryMiniGame");
}

std::string InventoryClown::GetObject(){
	return "InventoryClown";
}
