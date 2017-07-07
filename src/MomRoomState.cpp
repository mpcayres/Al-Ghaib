#include "MomRoomState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "Walls.hpp"
#include "EmptyBox.hpp"
#include "SceneDoor.hpp"
#include "SceneCovil.hpp"
#include "SceneObject.hpp"
#include "ScenePortal.hpp"
#include "SceneAnimated.hpp"
#include "MovingObject.hpp"
#include "StealthObject.hpp"
#include "SceneUntouchable.hpp"

#include <iostream>

MomRoomState::MomRoomState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x, int y) :
	State(), tileSetChao(144, 120, "img/tileSet/tileset_chao.png"),
	tileSetParede(144, 129, "img/tileSet/tileset_mom_parede.png"), tileMapChao("map/tileMapMomChao.txt", &tileSetChao),
	tileMapParede("map/tileMapMomParede.txt", &tileSetParede){

	limits = tileMapChao.FindLimits();
	if(x != -1 && y != -1) SetPlayer(x, y, CAMERA_TYPE1, limits);
	else SetPlayer(200, 400, CAMERA_TYPE1, limits);
	std::cout << "Player: " << MissionManager::player->box.x << " " << MissionManager::player->box.y << std::endl;

	if(inicial){
		//std::cout << "MR1.1 " << objectArray.size() << std::endl;
		SetInitialObjectArray();
		objectArray.insert( objectArray.end(),
				std::make_move_iterator(obj.begin()),
				std::make_move_iterator(obj.end()) );
	} else{
		//std::cout << "MR1.2 " << objectArray.size() << std::endl;
		objectArray = std::move(obj);
	}

	//objectArray.emplace_back(MissionManager::cat);
	objectArray.emplace_back(MissionManager::enemy);
	objectArray.emplace_back(MissionManager::player);

	RandomState();
	LoadAssets();
	std::cout << "MR2 " << objectArray.size() << std::endl;
}

MomRoomState::~MomRoomState() {
	objectArray.clear();
}

void MomRoomState::Pause(){
}

void MomRoomState::Resume(){
}

void MomRoomState::LoadAssets(){
	bg.Open("img/HUD/blackBack.jpg");
	background.Open("img/HUD/blackBack.jpg");
}

void MomRoomState::Update(float dt){
	InputManager instance = InputManager::GetInstance();

	if(instance.KeyPress(ESCAPE_KEY)){
		EndState();
	}
	if(instance.KeyPress(Q_KEY)){
		ChangeState("MomRoomState", "StageState");
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
		ChangeState("MomRoomState",
				((SceneDoor*)objectArray[changeIndex].get())->GetDest(), 800, 300, (int) Player::SUL);
	}
}

void MomRoomState::Render(){
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

void MomRoomState::SetInitialObjectArray(){
	EmptyBox* EB = new EmptyBox();
	objectArray.emplace_back(EB);

	SceneCovil* Covil =  new SceneCovil(540, 485);
	objectArray.emplace_back(Covil);

	SceneDoor* DoorToHall = new SceneDoor(220, 170, "HallState", false, "img/cenario/geral/door-closed.png", "img/cenario/geral/door-opened.png");
	objectArray.emplace_back(DoorToHall);

	StealthObject* Mesa = new StealthObject(170, 480, "img/cenario/geral/mesa.png");
	objectArray.emplace_back(Mesa);

	SceneUntouchable* Mirror = new SceneUntouchable(350, 150, "img/cenario/mae/espelho.png");
	objectArray.emplace_back(Mirror);

	SceneObject* Table = new SceneObject(375, 250, "img/cenario/mae/mesinha.png", "", 0, 0.7, 0.7);
	objectArray.emplace_back(Table);

	SceneObject* Armario =  new SceneObject(600, 200, "img/cenario/geral/armario-corredor-fechado.png", "img/cenario/geral/armario-corredor-aberto.png");
	objectArray.emplace_back(Armario);

	SceneObject* Cama =  new SceneObject(500, 200, "img/cenario/filho/cama.png", "");
	objectArray.emplace_back(Cama);

	SceneObject* CriadoMudo = new SceneObject(510, 320,  "img/cenario/filho/criado-fechado.png",  "img/cenario/filho/criado-aberto.png");
	objectArray.emplace_back(CriadoMudo);

	SceneObject* Book = new SceneObject(520, 320, "img/cenario/geral/livro.png", "img/cenario/geral/livro.png", 0, 0.3, 0.3);
	objectArray.emplace_back(Book);

	SceneObject* Mask = new SceneObject(650, 480, "img/cenario/mae/cabideiro.png", "");
	objectArray.emplace_back(Mask);

	MovingObject* Banco1 = new MovingObject(220, 510, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(Banco1);

}
