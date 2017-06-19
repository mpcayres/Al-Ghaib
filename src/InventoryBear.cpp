#include "InventoryBear.hpp"

InventoryBear::InventoryBear(/*std::string file*/){
	//Acho melhor n�o passar como string pq a� s� est� atrelado a pr�pria classe, n�o depende de outra ter essa info
	std::cout <<"ate aqui ok 1 " << std::endl;
	sp = Sprite( "img/obj_bear_1.png");
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
