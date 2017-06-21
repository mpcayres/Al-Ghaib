#include "HallState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "Walls.hpp"
#include "EmptyBox.hpp"
#include "SceneDoor.hpp"
#include "MovingObject.hpp"
#include "StealthObject.hpp"

#include <iostream>

HallState::HallState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial, int x, int y) :
	State(), tileSet(192, 96, "img/tilesetHall.png"), tileMap("map/tileMapHall.txt", &tileSet) {

	limits = tileMap.FindLimits();
	if(x != -1 && y != -1) SetPlayer(x, y, CAMERA_TYPE2, limits);
	else SetPlayer(450, 400, CAMERA_TYPE2, limits);
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
	objectArray.emplace_back(MissionManager::player);

	LoadAssets();
	//std::cout << "HSC2" << std::endl;
}

HallState::~HallState() {
	objectArray.clear();
}

void HallState::Pause(){
}

void HallState::Resume(){
}

void HallState::LoadAssets(){
	background.Open("img/ocean.jpg");
	bg.Open("img/corredor.png");
}

void HallState::Update(float dt){
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
				ChangeState(std::move(objectArray), "HallState", "StageState");
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
				ChangeState(std::move(objectArray), "HallState",
						((SceneDoor*)objectArray[changeIndex].get())->GetDest(), 800, 300, (int) Player::SUL);
		//std::cout << "DOOR4" << std::endl;
	}
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

	SceneObject* Window = new SceneObject(700, 70, "img/openwindow.png", "img/closedwindow.png", 0, 0.8, 0.8);
	objectArray.emplace_back(Window);

	SceneObject* CriadoMudo = new SceneObject(100, 160, "img/scene-criado-fechado.png", "img/scene-criado-fechado.png");
	objectArray.emplace_back(CriadoMudo);

	SceneObject* Book = new SceneObject(110, 150, "img/object-livro.png", "img/object-livro.png", 0, 0.3, 0.3);
	objectArray.emplace_back(Book);

	SceneDoor* DoorToKidRoom = new SceneDoor(400, 303, "StageState", false);
	objectArray.emplace_back(DoorToKidRoom);

	SceneObject* Table = new SceneObject(340, 303, "img/scene-mesa.png", "img/scene-mesa.png");
	objectArray.emplace_back(Table);

	StealthObject* Armario = new StealthObject(500, 305, "img/scene-armario-corredor-fechado.png");
	objectArray.emplace_back(Armario);

	SceneDoor* DoorToMomRoom = new SceneDoor(970, 105, "StageState");
	objectArray.emplace_back(DoorToMomRoom);

	SceneDoor* DoorToLivingRoom = new SceneDoor(500, 105, "LivingRoomState");
	objectArray.emplace_back(DoorToLivingRoom);

	StealthObject* Armario2 = new StealthObject(1400, 110, "img/scene-armario-corredor-fechado.png");
	objectArray.emplace_back(Armario2);

	SceneObject* Abajur = new SceneObject(1300, 300, "img/scene-abajur.png", "img/scene-abajur.png");
	objectArray.emplace_back(Abajur);

}
