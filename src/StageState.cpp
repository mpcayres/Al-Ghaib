#include "StageState.hpp"
#include "InputManager.hpp"
#include "Resources.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Music.hpp"
#include "EndState.hpp"
#include "Enemy.hpp"
#include "SceneObject.hpp"
#include "SceneWindow.hpp"
#include "SceneDoor.hpp"
#include "MovingObject.hpp"
#include "EmptyBox.hpp"
#include "Walls.hpp"
#include "MissionManager.hpp"

#include <iostream>

StageState::StageState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x, int y) :
	State(), tileSet(192, 96, "img/tileset.png"), tileMap("map/tileMap.txt", &tileSet) {

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
		std::vector<std::string> inventory = MissionManager::player->GetStringInventory();
		RemovePlayer();
		Game::GetInstance().GetMissionManager().
				ChangeMission(2, MissionManager::player->GetInHandIndex(), inventory);
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
					if(posInvert == -1 || i < posInvert) posInvert = i;
				}
				if(objectArray[j].get()->NotifyCollision(*objectArray[i].get())){
					if(posInvert == -1 || j < posInvert) posInvert = j;;
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
				ChangeState(std::move(objectArray), "StageState",
						((SceneDoor*)objectArray[changeIndex].get())->GetDest(), 500, 200, (int) Player::SUL);
		//std::cout << "DOOR4" << std::endl;
	}
}

void StageState::Render(){
	bg.Render(0,0,0);
	tileMap.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	RenderArray();

	if(MissionManager::player->GetShowingInventory()){
		MissionManager::player->RenderInventory();
	} else{
		MissionManager::player->RenderInHand();
		MissionManager::player->RenderNoise();
	}
}

void StageState::SetInitialObjectArray(){
	EmptyBox* EB = new EmptyBox();
	objectArray.emplace_back(EB);
	//Walls *Wall = new Walls(700, 400, 100,100);
	//objectArray.emplace_back(Wall);
	SceneDoor* Door = new SceneDoor(800, 200, "HallState");
	objectArray.emplace_back(Door);


	SceneWindow* Window = new SceneWindow(500, 200);
	objectArray.emplace_back(Window);

	SceneObject* Cama =  new SceneObject(200, 250, "img/scene-cama.png", "img/scene-cama.png");
	objectArray.emplace_back(Cama);

	SceneObject* Abajur =  new SceneObject(800, 400, "img/scene-abajur.png", "img/scene-abajur.png");
	objectArray.emplace_back(Abajur);

	SceneObject* Bau = new SceneObject(1000, 250,  "img/scene-bau-fechado.png", "img/scene-bau-fechado.png");
	objectArray.emplace_back(Bau);

}
