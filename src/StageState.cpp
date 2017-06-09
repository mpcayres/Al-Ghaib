#include "StageState.hpp"
#include "InputManager.hpp"
#include "Resources.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Music.hpp"
#include "EndState.hpp"
#include "Enemy.hpp"
#include "SceneWindow.hpp"
#include "SceneDoor.hpp"
#include "MovingObject.hpp"
#include "EmptyBox.hpp"
#include "Walls.hpp"
#include "MissionManager.hpp"

#include <iostream>

StageState::StageState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x, int y) :
	tileSet(64, 64, "img/tileset.png"), tileMap("map/tileMap.txt", &tileSet) {

	limits = tileMap.FindLimits();
	if(x != -1 && y != -1) SetPlayer(x, y, CAMERA_TYPE1, limits);
	else SetPlayer(600, 400, CAMERA_TYPE1, limits);
	if(inicial){
		//std::cout << "SSC1.1" << std::endl;
		SetInitialObjectArray();
		objectArray.insert( objectArray.end(),
				std::make_move_iterator(obj.begin()),
				std::make_move_iterator(obj.end()) );
	} else{
		//std::cout << "SSC1.2" << std::endl;
		objectArray = std::move(obj);
	}
	objectArray.emplace_back(MissionManager::player);

	music = Music("audio/stageState.ogg");
	quitRequested = false;
	popRequested = false;
	time = Timer();
	flagMorte = false;
	LoadAssets();
	//std::cout << "SSC2" << std::endl;
}

StageState::~StageState(){
	objectArray.clear();
}

void StageState::Pause(){
	music.Stop();
}

void StageState::Resume(){
	//music.Play(-1);
}

void StageState::LoadAssets(){
	bg.Open("img/ocean.jpg");
}

void StageState::Update(float dt){
	InputManager instance = InputManager::GetInstance();
	time.Update(dt);
	if(instance.KeyPress(ESCAPE_KEY)){
		popRequested = true;
		Camera::Unfollow();
		//RemovePlayer(typeid(*MissionManager::player).name());
		//MissionManager::DeletePlayer();
	}
	/*if(MissionManager::player == nullptr){
		if(flagMorte == false){
			time.Restart();
			flagMorte = true;
		}

		if(time.Get() >= 1.5 && flagMorte == true){
			popRequested = true;
			Camera::Unfollow();
			stateData.playerVictory = false;
			//Game::GetInstance().Push(new EndState(stateData));
		}
	}*/
	if(instance.KeyPress(W_KEY)){
		popRequested = true;
		Camera::Unfollow();
		RemovePlayer();
		Game::GetInstance().GetMissionManager().
				ChangeState(std::move(objectArray), "StageState", "HallState");
	}
	if(instance.KeyPress(A_KEY)){
		popRequested = true;
		Camera::Unfollow();
		std::vector<InventoryObject*> inventory = MissionManager::player->GetInventory();
		std::vector<std::string> oldInventory;
		for(unsigned int i = 0; i < inventory.size(); i++){
			std::string aux = std::move(inventory[i]->GetObject());
			oldInventory.emplace_back(aux);
		}
		inventory.clear();
		RemovePlayer();
		Game::GetInstance().GetMissionManager().
				ChangeMission(2, MissionManager::player->GetInHandIndex(), oldInventory);
	}
	quitRequested = instance.QuitRequested();

	Camera::Update(dt);
	UpdateArray(dt);

	int changeIndex = -1;
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

				objectArray[i].get()->NotifyCollision(*objectArray[j].get());
				objectArray[j].get()->NotifyCollision(*objectArray[i].get());

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
				ChangeState(std::move(objectArray), "StageState",
						((SceneDoor*)objectArray[changeIndex].get())->GetDest(),
						MissionManager::player->box.x, MissionManager::player->box.y);
		//std::cout << "DOOR4" << std::endl;
	}
}

void StageState::Render(){
	bg.Render(0,0,0);
	tileMap.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	RenderArray();
	//tileMap.Render(Camera::pos.x, Camera::pos.y);

	if(MissionManager::player->GetShowingInventory()){
		MissionManager::player->RenderInventory();
	} else{
		MissionManager::player->RenderInHand();
		MissionManager::player->RenderNoise();
	}
}

void StageState::SetInitialObjectArray(){
	EmptyBox* EB = new EmptyBox();
	//Walls *Wall = new Walls(700, 400, 100,100);
	//Enemy* E = new Enemy(1100, 500);
	SceneDoor* Door = new SceneDoor(800, 200, "img/doorclosed.png", "img/dooropened.png", "HallState");
	SceneWindow* Window = new SceneWindow(500, 200, "img/closedwindow.png", "img/openwindow.png");

	MovingObject* Table = new MovingObject(500, 400, "img/box.png");
	Table->SetMovementLimits(limits);

	objectArray.emplace_back(EB);
	//objectArray.emplace_back(Wall);
	//objectArray.emplace_back(E);
	objectArray.emplace_back(Window);
	objectArray.emplace_back(Door);
	objectArray.emplace_back(Table);
}
