#include "HallState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "Walls.hpp"
#include "PickUpObject.hpp"
#include "EmptyBox.hpp"
#include "SceneDoor.hpp"

#include <iostream>

HallState::HallState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial) {
	if(inicial){
		std::cout << "HSC1.1" << std::endl;
		SetInitialObjectArray();
		objectArray.insert( objectArray.end(),
				std::make_move_iterator(obj.begin()),
				std::make_move_iterator(obj.end()) );
	} else{
		std::cout << "HSC1.2" << std::endl;
		objectArray = std::move(obj);
		MissionManager::player->SetPosition(400,400);
		Camera::Follow(MissionManager::player, CAMERA_TYPE2);
		MissionManager::player->SetMovementLimits(Rect(-1500,-15000,13500,53000));
	}

	quitRequested = false;
	popRequested = false;
	LoadAssets();
	std::cout << "HSC2" << std::endl;
}

HallState::~HallState() {
	Camera::Unfollow();
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
		Game::GetInstance().GetMissionManager().
				ChangeState(std::move(objectArray), "HallState", "StageState");
	}
	quitRequested = instance.QuitRequested();

	Camera::Update(dt);
	UpdateArray(dt);

	for(int i = objectArray.size() - 1; i >= 0; --i) {
		/*if(objectArray[i].get()->Is("SceneDoor")){
			//std::cout << "DOOR" << std::endl;
			if(((SceneDoor*)objectArray[i].get())->GetChangeState()){
				//std::cout << "DOOR2" << std::endl;
				((SceneDoor*)objectArray[i].get())->SetChangeState(false);
				popRequested = true;
				Camera::Unfollow();
				//RemovePlayer(typeid(*MissionManager::player).name());
				std::cout << "DOOR3 " << ((SceneDoor*)objectArray[i].get())->GetDest() << std::endl;
				//Nao sei pq aqui nao esta funcionando
				Game::GetInstance().GetMissionManager().
						ChangeState(std::move(objectArray), "HallState", ((SceneDoor*)objectArray[i].get())->GetDest());
				std::cout << "DOOR4" << std::endl;
			}
		}*/
		for(int j = i-1; j >= 0; --j){
			if(Collision::IsColliding(objectArray[i].get()->box, objectArray[j].get()->box,
				objectArray[i].get()->rotation*PI/180, objectArray[j].get()->rotation*PI/180)){

				objectArray[i].get()->NotifyCollision(*objectArray[j].get());
				objectArray[j].get()->NotifyCollision(*objectArray[i].get());

			}
		}
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
	MissionManager::player->SetPosition(400,400);
	Camera::Follow(MissionManager::player, CAMERA_TYPE2);
	MissionManager::player->SetMovementLimits(Rect(-1500,-15000,13500,53000));
	EmptyBox* EB = new EmptyBox();

	//Walls *Wall1 = new Walls(605, 260, 141, 135);
	//Walls *Wall2 = new Walls(1061, 260, 141, 135);
	PickUpObject* PO = new PickUpObject(500, 400, "KeyObject", "img/minionbullet1.png");
	SceneDoor* Door = new SceneDoor(500, 100, "img/doorclosed.png", "img/dooropened.png", "StageState");

	objectArray.emplace_back(MissionManager::player);
	objectArray.emplace_back(EB);
	//objectArray.emplace_back(Wall1);
	//objectArray.emplace_back(Wall2);
	objectArray.emplace_back(PO);
	objectArray.emplace_back(Door);
}
