#include "LivingRoomState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "Walls.hpp"
#include "EmptyBox.hpp"
#include "SceneDoor.hpp"
#include "MovingObject.hpp"

#include <iostream>

LivingRoomState::LivingRoomState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x, int y) :
	State(), tileSet(192, 96, "img/tileset.png"), tileMap("map/tileMap.txt", &tileSet) {

	limits = tileMap.FindLimits();
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
	objectArray.emplace_back(MissionManager::player);

	RandomState();
	LoadAssets();
	//std::cout << "HSC2" << std::endl;
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
		//MissionManager::DeletePlayer();
	}
	if(instance.KeyPress(W_KEY)){
		popRequested = true;
		Camera::Unfollow();
		RemovePlayer();
		Game::GetInstance().GetMissionManager().
				ChangeState(std::move(objectArray), "LivingRoomState", "StageState");
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
		//std::cout << "DOOR2 " << changeIndex << std::endl;
		((SceneDoor*)objectArray[changeIndex].get())->SetChangeState(false);
		popRequested = true;
		Camera::Unfollow();
		RemovePlayer();
		//std::cout << "DOOR3 " << ((SceneDoor*)objectArray[changeIndex].get())->GetDest() << std::endl;
		//Nao sei pq aqui nao esta funcionando
		Game::GetInstance().GetMissionManager().
				ChangeState(std::move(objectArray), "LivingRoomState",
						((SceneDoor*)objectArray[changeIndex].get())->GetDest(), 800, 300, (int) Player::SUL);
		//std::cout << "DOOR4" << std::endl;
	}
}

void LivingRoomState::Render(){
	background.Render(0,0,0);
	bg.Render(0 - Camera::pos.x, Camera::pos.y+33,0);
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

void LivingRoomState::SetInitialObjectArray(){
	EmptyBox* EB = new EmptyBox();
	objectArray.emplace_back(EB);
}
