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
	State(), tileSet(192, 96, "img/tilesetHallFinal.png"), tileMap("map/tileMapHallFinal.txt", &tileSet) {
	//std::cout << "TESTE 1" << std::endl;
	limits = tileMap.FindLimits();

	SetPlayer(50, 310, CAMERA_TYPE2, limits);
	//std::cout << "HFSC1.1" << std::endl;
	SetInitialObjectArray();



	objectArray.emplace_back(MissionManager::enemy);
	//objectArray.emplace_back(MissionManager::cat);
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
	background.Open("img/HUD/semired.jpg");
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

	/* area de cheat de missao*/
		if(instance.KeyPress(W_KEY)){
			ChangeState("StageState", "HallState");
		} else if(instance.KeyPress(E_KEY)){
			ChangeState("StageState", "LivingRoomState");
		} else if(instance.KeyPress(R_KEY)){
			ChangeState("StageState", "MomRoomState");
		}else if(instance.KeyPress(T_KEY)){
			ChangeState("StageState", "HallFinalState");
		}else if(instance.KeyPress(KEY_1)){
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

	MovingObject* Banquinho1 = new MovingObject(560, 390, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(Banquinho1);

	MovingObject* Banquinho2 = new MovingObject(900, 400, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(Banquinho2);

	MovingObject* Banquinho3 = new MovingObject(1111, 300, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(Banquinho3);

	MovingObject* Vaso1 = new MovingObject(1760, 369, "img/cenario/geral/vaso.png", false);
			objectArray.emplace_back(Vaso1);

	MovingObject* Vaso2 = new MovingObject(1900, 369, "img/cenario/geral/vaso.png", false);
			objectArray.emplace_back(Vaso2);

	SceneObject* Bau= new SceneObject(2900, 260,
				"img/cenario/geral/bau-fechado.png", "img/cenario/geral/bau-aberto.png");
	objectArray.emplace_back(Bau);


	MovingObject* Cadeira = new MovingObject(2320, 280, "img/cenario/geral/cadeira.png", true);
		objectArray.emplace_back(Cadeira);

	MovingObject* BanquinhoBlock1 = new MovingObject(4100, 300, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(BanquinhoBlock1);

	MovingObject* BanquinhoBlock2 = new MovingObject(4250, 300, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(BanquinhoBlock2);

	MovingObject* BanquinhoBlock3 = new MovingObject(4150, 350, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(BanquinhoBlock3);

	MovingObject* BanquinhoBlock4 = new MovingObject(4200, 350, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(BanquinhoBlock4);

	//SceneObject* Livro = new SceneObject(3175, 300, "img/cenario/geral/livro.png", "img/cenario/geral/livro.png" , 0, 0.4, 0.4);
	//objectArray.emplace_back(Livro);

	StealthObject* Armario = new StealthObject(5500, 210, "img/cenario/geral/armario-corredor-fechado.png");
		objectArray.emplace_back(Armario);

	SceneDoor* DoorToKidRoom = new SceneDoor(6000, 200, "StageState", false);
		objectArray.emplace_back(DoorToKidRoom);
}
