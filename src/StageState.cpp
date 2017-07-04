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
#include "SceneDoor.hpp"
#include "MovingObject.hpp"
#include "StealthObject.hpp"
#include "EmptyBox.hpp"
#include "Walls.hpp"
#include "MissionManager.hpp"

#include <iostream>


StageState::StageState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x, int y) :
	State(), tileSet(192, 96, "img/tileset.png"), tileMap("map/tileMap.txt", &tileSet) {

	limits = tileMap.FindLimits();
	limits.y -= 50;
	MissionManager::player->AddWallLimits(Rect(600, 192, 200, 80));
	if(x != -1 && y != -1) SetPlayer(x, y, CAMERA_TYPE3, limits);
	else SetPlayer(550, 400, CAMERA_TYPE3, limits);
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

	RandomState();

	music = Music("audio/ambiente.wav");
	time = Timer();
	flagMorte = false;
	LoadAssets();
	std::cout << "SSC2 "  << objectArray.size() << std::endl;
}

StageState::~StageState(){
	objectArray.clear();
}

void StageState::Pause(){
	music.Stop();
}

void StageState::Resume(){
	music.Play(-1);
}

void StageState::LoadAssets(){
	bg.Open("img/ocean.jpg");
}

void StageState::Update(float dt){
	InputManager instance = InputManager::GetInstance();
	time.Update(dt);

	if(instance.KeyPress(ESCAPE_KEY)){
		EndState();
	}

	/* area de cheat de missao*/
	if(instance.KeyPress(W_KEY)){
		ChangeState("StageState", "HallState");
	} else if(instance.KeyPress(E_KEY)){
		ChangeState("StageState", "LivingRoomState");
	} else if(instance.KeyPress(R_KEY)){
		ChangeState("StageState", "MomRoomState");
	} else if(instance.KeyPress(KEY_1)){
		ChangeMission(1);
	}else if(instance.KeyPress(KEY_2)){
		ChangeMission(2);
	} else if(instance.KeyPress(KEY_3)){
		ChangeMission(3);
	} else if(instance.KeyPress(KEY_4)){
		ChangeMission(4);
	} else if(instance.KeyPress(KEY_5)){
		ChangeMission(5);
	} else if(instance.KeyPress(KEY_6)){
		ChangeMission(6);
	}

	/* fim de area de cheat de missao*/
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
		((SceneDoor*)objectArray[changeIndex].get())->SetChangeState(false);
		ChangeState("StageState",
				((SceneDoor*)objectArray[changeIndex].get())->GetDest(), 400, 380, (int) Player::SUL);
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

	SceneObject* Escrivaninha = new SceneObject(650, 440, "img/scene-escrivaninha-fechado.png", "img/scene-escrivaninha-aberto.png");
	objectArray.emplace_back(Escrivaninha);

	StealthObject* Mesa = new StealthObject(900, 400, "img/scene-mesa.png");
	objectArray.emplace_back(Mesa);

	SceneObject* Window = new SceneObject(540, 200, "img/closedwindow.png", "img/openwindow.png", 0, 0.7, 0.7);
	objectArray.emplace_back(Window);

	SceneObject* Cama =  new SceneObject(200, 260, "img/scene-cama.png", "");
	objectArray.emplace_back(Cama);

	SceneObject* Armario =  new SceneObject(430, 240, "img/scene-armario-quarto-fechado.png", "img/scene-armario-quarto-fechado.png");
	objectArray.emplace_back(Armario);

	SceneObject* Abajur =  new SceneObject(600, 200, "img/scene-abajur.png", "");
	objectArray.emplace_back(Abajur);

	MovingObject* Vaso = new MovingObject(900, 300,  "img/scene-vaso.png");
	objectArray.emplace_back(Vaso);

}
