#include "HallState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "Walls.hpp"
#include "EmptyBox.hpp"
#include "SceneDoor.hpp"
#include "ScenePortal.hpp"
#include "MovingObject.hpp"
#include "StealthObject.hpp"
#include "SceneUntouchable.hpp"

#include <iostream>

HallState::HallState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x, int y) :
	State(), tileSet(192, 96, "img/tilesetHall.png"), tileMap("map/tileMapHall.txt", &tileSet) {

	limits = tileMap.FindLimits();
	limits.y -=50;
	MissionManager::player->AddWallLimits(Rect(0, 0, 768, 180 ));
	MissionManager::player->AddWallLimits(Rect(960, 0, 576, 180 ));

	if(x != -1 && y != -1) SetPlayer(x, y, CAMERA_TYPE2, limits);
	else SetPlayer(50, 400, CAMERA_TYPE2, limits);
	std::cout << "Player: " << MissionManager::player->box.x << " " << MissionManager::player->box.y << std::endl;

	std::vector<Rect> auxLimits = tileMap.GetInnerLimits();
	for(unsigned i = 0; i < auxLimits.size(); i++){
		MissionManager::player->AddWallLimits(auxLimits[i]);
	}

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
	objectArray.emplace_back(MissionManager::cat);
	objectArray.emplace_back(MissionManager::enemy);
	objectArray.emplace_back(MissionManager::player);

	for(int i = objectArray.size() - 1; i >= 0; --i) {
		if(objectArray[i].get()->Is("SceneDoor")){
			if(MissionManager::missionManager->IsPreviousState(((SceneDoor*)objectArray[i].get())->GetDest())){
				((SceneDoor*)objectArray[i].get())->ChangeImage(true);
			}
		}
	}

	RandomState();
	LoadAssets();
	std::cout << "HSC2 " << objectArray.size() << std::endl;
}

HallState::~HallState() {
	objectArray.clear();
}

void HallState::Pause(){
}

void HallState::Resume(){
}

void HallState::LoadAssets(){
	background.Open("img/HUD/blackBack.jpg");
	bg.Open("img/corredor.png");
}

void HallState::Update(float dt){
	InputManager instance = InputManager::GetInstance();

	if(instance.KeyPress(ESCAPE_KEY)){
		EndState();
	}
	if(instance.KeyPress(W_KEY)){
		ChangeState("HallState", "StageState");
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
		if(((SceneDoor*)objectArray[changeIndex].get())->GetDest() == "StageState"){
			ChangeState("HallState", "StageState", 800, 280, (int) Player::SUL);
		} else if(((SceneDoor*)objectArray[changeIndex].get())->GetDest() == "LivingRoomState"){
			ChangeState("HallState", "LivingRoomState", 240, 200, (int) Player::SUL);
		} else if(((SceneDoor*)objectArray[changeIndex].get())->GetDest() == "MomRoomState"){
			ChangeState("HallState", "MomRoomState", 230, 210, (int) Player::SUL);
		}
	}

	/*if(MissionManager::missionManager->setObjectTile){
		tileMap.AddObjects();
		MissionManager::missionManager->setObjectTile = false;
	}*/

}

void HallState::Render(){
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

void HallState::SetInitialObjectArray(){
	EmptyBox* EB = new EmptyBox();
	objectArray.emplace_back(EB);

	SceneObject* Table = new SceneObject(340, 303, "img/cenario/geral/mesa.png", "");
	objectArray.emplace_back(Table);

	SceneDoor* DoorToKidRoom = new SceneDoor(400, 303, "StageState", false);
	objectArray.emplace_back(DoorToKidRoom);

	ScenePortal* DoorToLivingRoom = new ScenePortal(500, 105, "LivingRoomState");
	objectArray.emplace_back(DoorToLivingRoom);

	//SceneObject* CriadoMudo = new SceneObject(100, 160, "img/cenario/filho/criado-fechado.png", "img/cenario/filho/criado-aberto.png");
	//objectArray.emplace_back(CriadoMudo);

	SceneObject* Book = new SceneObject(110, 150, "img/cenario/geral/livro.png", "img/cenario/geral/livro.png", 0, 0.3, 0.3);
	objectArray.emplace_back(Book);

	SceneObject* Abajur = new SceneObject(1300, 310, "img/cenario/geral/abajur.png", "img/cenario/geral/abajur.png");
	objectArray.emplace_back(Abajur);

	SceneUntouchable* Rug = new SceneUntouchable(700, 310, "img/cenario/geral/tapete.png");
	objectArray.emplace_back(Rug);

	StealthObject* Armario = new StealthObject(500, 305, "img/cenario/geral/armario-corredor-fechado.png");
	objectArray.emplace_back(Armario);

	//StealthObject* Armario2 = new StealthObject(1400, 110, "img/cenario/armario-corredor-fechado.png");
	//objectArray.emplace_back(Armario2);

}
