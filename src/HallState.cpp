#include "HallState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "Walls.hpp"
#include "EmptyBox.hpp"
#include "SceneDoor.hpp"
#include "MovingObject.hpp"

#include <iostream>

HallState::HallState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial) {
	limits = Rect(-1500,-15000,13500,53000);//tileMap.FindLimits();
	SetPlayer(450, 400, CAMERA_TYPE2, limits);
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

	quitRequested = false;
	popRequested = false;
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
				ChangeState(std::move(objectArray), "HallState",
						((SceneDoor*)objectArray[changeIndex].get())->GetDest());
		//std::cout << "DOOR4" << std::endl;
	}
}

void HallState::Render(){
	background.Render(0,0,0);
	bg.Render(0 - Camera::pos.x, Camera::pos.y,0);
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

	Walls *Wall1 = new Walls(270, 282, 130, 125);
	Walls *Wall2 = new Walls(725, 282, 130, 125);
	Walls *Wall3 = new Walls(1175, 282, 130, 125);
	SceneDoor* Door = new SceneDoor(500, 100, "img/doorclosed.png", "img/dooropened.png", "StageState");

	MovingObject* Table = new MovingObject(500, 200, "img/box.png");
	Table->SetMovementLimits(limits);

	objectArray.emplace_back(EB);
	objectArray.emplace_back(Wall1);
	objectArray.emplace_back(Wall2);
	objectArray.emplace_back(Wall3);
	objectArray.emplace_back(Door);
	objectArray.emplace_back(Table);
}
