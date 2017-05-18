#include "InventoryKey.hpp"

InventoryKey::InventoryKey(/*std::string file*/){
	//Acho melhor não passar como string pq aí só está atrelado a própria classe, não depende de outra ter essa info
	sp = Sprite("img/minion.png");
}

InventoryKey::~InventoryKey(){
}

void InventoryKey::Render(){
	sp.Render(0,0,0);
}

void InventoryKey::Action(){ }

bool InventoryKey::IsObject(std::string type){
	return (type == "KeyObject");
}
