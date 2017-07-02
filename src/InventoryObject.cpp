#include "InventoryObject.hpp"

InventoryObject::InventoryObject(std::string file){
	sp = Sprite(file);
}

InventoryObject::~InventoryObject(){ }

void InventoryObject::Render(int x, int y){
	sp.Render(x, y, 0);
}

int InventoryObject::GetWidth(){ return sp.GetScaledWidth();}

int InventoryObject::GetHeight(){ return sp.GetScaledHeight(); }

void InventoryObject::SetScaleX(float scale) { sp.SetScaleX(scale);}

void InventoryObject::SetScaleY(float scale) { sp.SetScaleY(scale);}
