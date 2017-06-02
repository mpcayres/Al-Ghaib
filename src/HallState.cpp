#include "HallState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "Walls.hpp"
#include "PickUpObject.hpp"

HallState::HallState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial) {
	if(inicial){
		SetInitialObjectArray();
	} else{
		objectArray = std::move(obj);
		P->SetPosition(400,400);
		Camera::Follow(P, CAMERA_TYPE2);
		P->SetMovementLimits(Rect(-1500,-15000,13500,53000));
	}

	quitRequested = false;
	LoadAssets();
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
	}
	quitRequested = instance.QuitRequested();

	if(instance.KeyPress(W_KEY)){
		popRequested = true;
		Camera::Unfollow();
		Game::GetInstance().GetMissionManager().
				ChangeState(std::move(objectArray), "HallState", "StageState");
	}
	if(Door->GetChangeState()){
		Door->SetChangeState(false);
		popRequested = true;
		Camera::Unfollow();
		Game::GetInstance().GetMissionManager().
				ChangeState(std::move(objectArray), "HallState", Door->GetDest());
	}

	Camera::Update(dt);
	UpdateArray(dt);

	/*for(int i = objectArray.size() - 1; i >= 0; --i) {
		for(int j = i-1; j >= 0; --j){
			if(Collision::IsColliding(objectArray[i].get()->box, objectArray[j].get()->box,
				objectArray[i].get()->rotation*PI/180, objectArray[j].get()->rotation*PI/180)){

				objectArray[i].get()->NotifyCollision(*objectArray[j].get());
				objectArray[j].get()->NotifyCollision(*objectArray[i].get());

			}
		}
	}*/
}

void HallState::Render(){
	background.Render(0,0,0);
	bg.Render(0 - Camera::pos.x, Camera::pos.y,0);
	RenderArray();

	/*if(Player::player->GetShowingInventory()){
		Player::player->RenderInventory();
	} else{
		Player::player->RenderInHand();
	}*/
}

void HallState::SetInitialObjectArray(){
	P = new Player(400,400);
	Camera::Follow(P, CAMERA_TYPE2);
	P->SetMovementLimits(Rect(-1500,-15000,13500,53000));

	//Walls *Wall1 = new Walls(605, 260, 141, 135);
	//Walls *Wall2 = new Walls(1061, 260, 141, 135);
	PickUpObject* PO = new PickUpObject(900, 400, "KeyObject", "img/minionbullet1.png");
	Door = new SceneDoor(800, 100, "img/doorclosed.png", "img/dooropened.png", "StageState");

	objectArray.emplace_back(Player::player);
	//objectArray.emplace_back(Wall1);
	//objectArray.emplace_back(Wall2);
	objectArray.emplace_back(PO);
	objectArray.emplace_back(Door);
}
