#include "InventoryMiniGame.hpp"
#include "MissionManager.hpp"

InventoryMiniGame::InventoryMiniGame(std::string file, std::string file2, std::string file3) :
	InventoryObject(file), sp2(file2), sp3(file3), timesPressed(0) {
	sp2.SetScaleX(0.6); sp2.SetScaleX(0.6);
	sp3.SetScaleY(0.6); sp3.SetScaleY(0.6);
}

InventoryMiniGame::~InventoryMiniGame(){ }

void InventoryMiniGame::Render(int x, int y){
	if(timesPressed < 5) sp.Render(x, y, 0);
	else if(timesPressed >= 5 && timesPressed < 20) sp2.Render(x, y, 0);
	if(timesPressed > 20) sp3.Render(x, y, 0);
}

bool InventoryMiniGame::Action(GameObject* other){
	timesPressed++;
	MissionManager::player->AddRuido(0.2*50);
	if(timesPressed > 30) return true;
	return false;
}

bool InventoryMiniGame::IsObject(std::string type){
	return (type == "InventoryMiniGame");
}

std::string InventoryMiniGame::GetObject(){
	return "InventoryMiniGame";
}
