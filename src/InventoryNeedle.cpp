#include "InventoryNeedle.hpp"
#include "SceneDoor.hpp"

InventoryNeedle::InventoryNeedle(){
	sp = Sprite("img/object-needle.png");
}

InventoryNeedle::~InventoryNeedle(){ }

void InventoryNeedle::Render(int x, int y){
	sp.Render(x, y, 0);
}

bool InventoryNeedle::Action(GameObject* other){
	/*if(other->Is("SceneDoor")){
		return (((SceneDoor*)other)->ReceiveAction(this));
	}*/
	return false;
}

bool InventoryNeedle::IsObject(std::string type){
	return (type == "InventoryNeedle");
}

std::string InventoryNeedle::GetObject(){
	return "InventoryNeedle";
}

int InventoryNeedle::GetWidth(){ return sp.GetScaledWidth();}

int InventoryNeedle::GetHeight(){ return sp.GetScaledHeight(); }

void InventoryNeedle::SetScaleX(float scale) { sp.SetScaleX(scale);}

void InventoryNeedle::SetScaleY(float scale) { sp.SetScaleY(scale);}
