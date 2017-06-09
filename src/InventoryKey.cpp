#include "InventoryKey.hpp"
#include "SceneDoor.hpp"

InventoryKey::InventoryKey(/*std::string file*/){
	//Acho melhor não passar como string pq aí só está atrelado a própria classe, não depende de outra ter essa info
	sp = Sprite("img/minionbullet1.png");
}

InventoryKey::~InventoryKey(){ }

void InventoryKey::Render(int x, int y){
	sp.Render(x, y, 0);
}

bool InventoryKey::Action(GameObject* other){
	if(other->Is("SceneDoor")){
		return (((SceneDoor*)other)->ReceiveAction(this));
	}
	return false;
}

bool InventoryKey::IsObject(std::string type){
	return (type == "InventoryKey");
}

std::string InventoryKey::GetObject(){
	return "InventoryKey";
}

int InventoryKey::GetWidth(){ return sp.GetScaledWidth();}

int InventoryKey::GetHeight(){ return sp.GetScaledHeight(); }

void InventoryKey::SetScaleX(float scale) { sp.SetScaleX(scale);}

void InventoryKey::SetScaleY(float scale) { sp.SetScaleY(scale);}

