#include "InventoryScissors.hpp"
#include "SceneDoor.hpp"

InventoryScissors::InventoryScissors(){
	sp = Sprite("img/object-scissors.png");
}

InventoryScissors::~InventoryScissors(){ }

void InventoryScissors::Render(int x, int y){
	sp.Render(x, y, 0);
}

bool InventoryScissors::Action(GameObject* other){
	/*if(other->Is("SceneDoor")){
		return (((SceneDoor*)other)->ReceiveAction(this));
	}*/
	return false;
}

bool InventoryScissors::IsObject(std::string type){
	return (type == "InventoryScissors");
}

std::string InventoryScissors::GetObject(){
	return "InventoryScissors";
}

int InventoryScissors::GetWidth(){ return sp.GetScaledWidth();}

int InventoryScissors::GetHeight(){ return sp.GetScaledHeight(); }

void InventoryScissors::SetScaleX(float scale) { sp.SetScaleX(scale);}

void InventoryScissors::SetScaleY(float scale) { sp.SetScaleY(scale);}
