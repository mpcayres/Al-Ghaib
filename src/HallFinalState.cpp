#include "HallFinalState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "EmptyBox.hpp"
#include "SceneDoor.hpp"
#include "ScenePortal.hpp"
#include "MovingObject.hpp"
#include "StealthObject.hpp"
#include "SceneUntouchable.hpp"

#include <iostream>

//NESSE STATE TUDO VAI SER SETADO DIRETO NELE
HallFinalState::HallFinalState() :
	State(), tileSet(192, 96, "img/tilesetHall.png"), tileMap("map/tileMapHall.txt", &tileSet) {
	//std::cout << "TESTE 1" << std::endl;
	limits = tileMap.FindLimits();
	limits.y -=50;
	MissionManager::player->AddWallLimits(Rect(0, 0, 768, 180 ));
	MissionManager::player->AddWallLimits(Rect(960, 0, 576, 180 ));

	SetPlayer(50, 400, CAMERA_TYPE2, limits);
	std::vector<Rect> auxLimits = tileMap.GetInnerLimits();
	for(unsigned i = 0; i < auxLimits.size(); i++){
		MissionManager::player->AddWallLimits(auxLimits[i]);
	}

	//std::cout << "HFSC1.1" << std::endl;
	SetInitialObjectArray();

	objectArray.emplace_back(MissionManager::enemy);
	objectArray.emplace_back(MissionManager::cat);
	objectArray.emplace_back(MissionManager::player);

	LoadAssets();
	std::cout << "HFSC2 " << objectArray.size() << std::endl;
}

HallFinalState::~HallFinalState() {
	objectArray.clear();
}

void HallFinalState::Pause(){
}

void HallFinalState::Resume(){
}

void HallFinalState::LoadAssets(){
	background.Open("img/HUD/blackBack.jpg");
	bg.Open("img/corredor.png");
}

void HallFinalState::Update(float dt){
	InputManager instance = InputManager::GetInstance();

	if(instance.KeyPress(ESCAPE_KEY)){
		EndState();
	}
	if(instance.KeyPress(W_KEY)){
		ChangeState("HallFinalState", "StageState");
	}
	quitRequested = instance.QuitRequested();

	Camera::Update(dt);
	UpdateArray(dt);

	int changeIndex = -1;
	posInvert = -1;
	for(int i = objectArray.size() - 1; i >= 0; --i) {
		if(objectArray[i].get()->Is("SceneDoor")){
			//std::cout << "DOOR" << std::endl;
			if(((SceneDoor*)objectArray[i].get())->GetChangeState()){
				changeIndex = i;
			}
		}
		for(int j = i-1; j >= 0; --j){
			if(Collision::IsColliding(objectArray[i].get()->box, objectArray[j].get()->box,
				objectArray[i].get()->rotation*PI/180, objectArray[j].get()->rotation*PI/180)){

				if(objectArray[i].get()->NotifyCollision(*objectArray[j].get())){
					if(i > posInvert) posInvert = i;
				}
				if(objectArray[j].get()->NotifyCollision(*objectArray[i].get())){
					if(j > posInvert) posInvert = j;;
				}

			}
		}
	}

	if(changeIndex != -1){
		((SceneDoor*)objectArray[changeIndex].get())->SetChangeState(false);
		ChangeState("HallFinalState",
				((SceneDoor*)objectArray[changeIndex].get())->GetDest(), 800, 300, (int) Player::SUL);
	}
}

void HallFinalState::Render(){
	background.Render(0,0,0);
	//bg.Render(0 - Camera::pos.x, Camera::pos.y+33,0);
	tileMap.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	//bg.Render(0,0,0);
	RenderArray();

	if(MissionManager::player->GetShowingInventory()){
		MissionManager::player->RenderInventory();
	} else{
		MissionManager::player->RenderInHand();
		MissionManager::player->RenderNoise();
	}
}

void HallFinalState::SetInitialObjectArray(){
	EmptyBox* EB = new EmptyBox();
	objectArray.emplace_back(EB);
}
