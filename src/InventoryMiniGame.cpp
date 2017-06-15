#include "InventoryMiniGame.hpp"
#include "MissionManager.hpp"

InventoryMiniGame::InventoryMiniGame(std::string file){
	sp = Sprite(file);
	timesPressed = 0;
}

InventoryMiniGame::~InventoryMiniGame(){ }

void InventoryMiniGame::Render(int x, int y){
	sp.Render(x, y, 0);
}

bool InventoryMiniGame::Action(GameObject* other){
	timesPressed++;
	MissionManager::player->AddRuido(0.2*50);
	if(timesPressed > 25) return true;
	return false;
}

bool InventoryMiniGame::IsObject(std::string type){
	return (type == "InventoryMiniGame");
}

std::string InventoryMiniGame::GetObject(){
	return "InventoryMiniGame";
}

int InventoryMiniGame::GetWidth(){ return sp.GetScaledWidth();}

int InventoryMiniGame::GetHeight(){ return sp.GetScaledHeight(); }

void InventoryMiniGame::SetScaleX(float scale) { sp.SetScaleX(scale);}

void InventoryMiniGame::SetScaleY(float scale) { sp.SetScaleY(scale);}
