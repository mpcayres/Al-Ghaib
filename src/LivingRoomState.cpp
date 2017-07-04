#include "LivingRoomState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "Walls.hpp"
#include "EmptyBox.hpp"
#include "SceneDoor.hpp"
#include "ScenePortal.hpp"
#include "MovingObject.hpp"
#include "StealthObject.hpp"

#include <iostream>

LivingRoomState::LivingRoomState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x, int y) :
	State(), tileSetChao(150, 117, "img/tileSet/tile_sala_chao.png"),
	tileSetParede(150, 126, "img/tileSet/tile_sala_parede.jpeg"), tileMapChao("map/tileMapSalaChao.txt", &tileSetChao),
	tileMapParede("map/tileMapSalaParede.txt", &tileSetParede){

	limits = tileMapChao.FindLimits();
	if(x != -1 && y != -1) SetPlayer(x, y, CAMERA_TYPE0, limits);
	else SetPlayer(600, 400, CAMERA_TYPE0, limits);
	//MissionManager::player->AddWallLimits(Rect(270, 282, 130, 125));
	//MissionManager::player->AddWallLimits(Rect(725, 282, 130, 125));
	//MissionManager::player->AddWallLimits(Rect(1175, 282, 130, 125));
	if(inicial){
		//std::cout << "HSC1.1" << std::endl;
		SetInitialObjectArray();
		objectArray.insert( objectArray.end(),
				std::make_move_iterator(obj.begin()),
				std::make_move_iterator(obj.end()) );
	} else{
		//std::cout << "HSC1.2" << std::endl;
		objectArray = std::move(obj);
	}
	objectArray.emplace_back(MissionManager::enemy);
	//objectArray.emplace_back(MissionManager::cat);
	objectArray.emplace_back(MissionManager::player);

	RandomState();
	LoadAssets();
	std::cout << "LR2" << std::endl;
}

LivingRoomState::~LivingRoomState() {
	objectArray.clear();
}

void LivingRoomState::Pause(){
}

void LivingRoomState::Resume(){
}

void LivingRoomState::LoadAssets(){
	bg.Open("img/ocean.jpg");
	background.Open("img/ocean.jpg");
}

void LivingRoomState::Update(float dt){
	InputManager instance = InputManager::GetInstance();

	if(instance.KeyPress(ESCAPE_KEY)){
		popRequested = true;
		Camera::Unfollow();
	}
	if(instance.KeyPress(W_KEY)){
		ChangeState("LivingRoomState", "StageState");
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
		ChangeState("LivingRoomState",
				((SceneDoor*)objectArray[changeIndex].get())->GetDest(), 800, 300, (int) Player::SUL);
	}
}

void LivingRoomState::Render(){
	background.Render(0,0,0);
	bg.Render(0 - Camera::pos.x, Camera::pos.y+33,0);
	tileMapChao.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	tileMapParede.RenderLayer(0, Camera::pos.x, Camera::pos.y);

	//bg.Render(0,0,0);
	RenderArray();

	if(MissionManager::player->GetShowingInventory()){
		MissionManager::player->RenderInventory();
	} else{
		MissionManager::player->RenderInHand();
		MissionManager::player->RenderNoise();
	}
}

void LivingRoomState::SetInitialObjectArray(){
	EmptyBox* EB = new EmptyBox();
	objectArray.emplace_back(EB);

	//MovingObject* Banco = new MovingObject(650, 370, "img/moveis/sala/banquinho.png", true);
	//objectArray.emplace_back(Banco);

	SceneObject* Sofa = new SceneObject(500, 320, "img/moveis/sala/sofa.png", "img/moveis/sala/sofa.png");
	objectArray.emplace_back(Sofa);

	SceneObject* Poltrona = new SceneObject(400, 330, "img/moveis/sala/poltrona.png", "img/moveis/sala/poltrona.png");
	objectArray.emplace_back(Poltrona);

	SceneObject* Mesa = new SceneObject(500, 380, "img/moveis/sala/mesa.png", "img/moveis/sala/mesa.png");
	objectArray.emplace_back(Mesa);

	SceneObject* TV = new SceneObject(630, 450, "img/moveis/sala/televisão_desligada.png", "img/moveis/sala/televisão_desligada.png");
	objectArray.emplace_back(TV);

	SceneObject* Painel = new SceneObject(390, 127, "img/moveis/sala/mosaico.png", "img/moveis/sala/mosaico.png");
	objectArray.emplace_back(Painel);

	SceneObject* Pilastra1 = new SceneObject(350, 127, "img/moveis/sala/pilastra.png", "img/moveis/sala/pilastra.png");
	objectArray.emplace_back(Pilastra1);

	SceneObject* Pilastra2 = new SceneObject(725, 127, "img/moveis/sala/pilastra.png", "img/moveis/sala/pilastra.png");
	objectArray.emplace_back(Pilastra2);

	SceneDoor* DoorToHall = new SceneDoor(220, 165, "HallState", false, "img/scene-portal.png", "img/scene-portal.png");
	objectArray.emplace_back(DoorToHall);

	SceneObject* Armario = new SceneObject(790, 175, "img/scene-armario-corredor-fechado.png", "img/scene-armario-corredor-fechado.png");
	objectArray.emplace_back(Armario);


	if( MissionManager::missionManager->GetNumMission() == 1   ){
		SceneObject* Bau = new SceneObject(400, 500,  "img/scene-bau-fechado.png",
					"img/scene-bau-aberto.png", 0, 1, 1, "InventoryBear", SceneObject::SAMEY_UP);
		objectArray.emplace_back(Bau);
	}

	if(MissionManager::player->HaveObject("InventoryKey") &&  MissionManager::missionManager->GetNumMission() != 1){
		SceneObject* Bau = new SceneObject(300, 490,  "img/scene-bau-fechado.png",
					"img/scene-bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
		objectArray.emplace_back(Bau);
	} else if ( MissionManager::missionManager->GetNumMission() != 1){
		SceneObject* Bau = new SceneObject(300, 490,  "img/scene-bau-fechado.png",
					"img/scene-bau-aberto.png", 0, 1, 1, "InventoryControl", SceneObject::SAMEY_UP);
		objectArray.emplace_back(Bau);
	}
}
