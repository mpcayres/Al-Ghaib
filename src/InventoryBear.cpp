#include "InventoryBear.hpp"

InventoryBear::InventoryBear(){
	sp = Sprite("img/object-bear.png");
}

InventoryBear::~InventoryBear(){ }

void InventoryBear::Render(int x, int y){
	sp.Render(x, y, 0);
}

bool InventoryBear::Action(GameObject* other){
	/*if(other->Is("SceneDoor")){
		return (((SceneDoor*)other)->ReceiveAction(this));
	}
	return false;*/
	return false;
}

bool InventoryBear::IsObject(std::string type){
	return (type == "InventoryBear");
}

std::string InventoryBear::GetObject(){
	return "InventoryBear";
}

int InventoryBear::GetWidth(){ return sp.GetScaledWidth();}

int InventoryBear::GetHeight(){ return sp.GetScaledHeight(); }

void InventoryBear::SetScaleX(float scale) { sp.SetScaleX(scale);}

void InventoryBear::SetScaleY(float scale) { sp.SetScaleY(scale);}
