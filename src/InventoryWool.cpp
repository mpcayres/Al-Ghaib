#include "InventoryWool.hpp"
#include "SceneDoor.hpp"

InventoryWool::InventoryWool(){
	sp = Sprite("img/obj_novelo.png");
}

InventoryWool::~InventoryWool(){ }

void InventoryWool::Render(int x, int y){
	sp.Render(x, y, 0);
}

bool InventoryWool::Action(GameObject* other){
	/*if(other->Is("SceneDoor")){
		return (((SceneDoor*)other)->ReceiveAction(this));
	}*/
	return false;
}

bool InventoryWool::IsObject(std::string type){
	return (type == "InventoryWool");
}

std::string InventoryWool::GetObject(){
	return "InventoryWool";
}

int InventoryWool::GetWidth(){ return sp.GetScaledWidth();}

int InventoryWool::GetHeight(){ return sp.GetScaledHeight(); }

void InventoryWool::SetScaleX(float scale) { sp.SetScaleX(scale);}

void InventoryWool::SetScaleY(float scale) { sp.SetScaleY(scale);}
