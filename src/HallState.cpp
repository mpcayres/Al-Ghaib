#include "HallState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "Collision.hpp"

HallState::HallState() {
	Player* P = new Player(400, 400);
	objectArray.emplace_back(P);
	//Camera::Follow(P);

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
	}
	quitRequested = instance.QuitRequested();

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
	bg.Render(0,0,0);
	RenderArray();

	/*if(Player::player->GetShowingInventory()){
		Player::player->RenderInventory();
	} else{
		Player::player->RenderInHand();
	}*/
}
