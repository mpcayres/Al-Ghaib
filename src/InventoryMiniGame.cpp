#include "InventoryMiniGame.hpp"
#include "MissionManager.hpp"

#include <iostream>

InventoryMiniGame::InventoryMiniGame(std::string file, std::string file2, std::string file3) :
	InventoryObject(file), file2(file2), file3(file3), timesPressed(0) {
}

InventoryMiniGame::~InventoryMiniGame(){ }

bool InventoryMiniGame::Action(GameObject* other){
	timesPressed++;
	if(timesPressed == 5){
		sp = Sprite(file2);
		sp.SetScaleX(0.6);
	}
	if(timesPressed == 20){
		sp = Sprite(file3);
		sp.SetScaleY(0.6);
	}
	MissionManager::player->AddRuido(0.2*50);
	if(timesPressed >= 30) return true;
	return false;
}

bool InventoryMiniGame::IsObject(std::string type){
	return (type == "InventoryMiniGame");
}

std::string InventoryMiniGame::GetObject(){
	return "InventoryMiniGame";
}
