#include "State.hpp"
#include "MissionManager.hpp"
#include "SceneObject.hpp"
#include "Camera.hpp"

#include <random>
#include <iostream>
#include <chrono>

State::State(){
	quitRequested = false;
	popRequested = false;
	posInvert = -1;
}

State::~State(){
	objectArray.clear();
}

void State::AddObject(GameObject *object){
	objectArray.emplace_back(object);
}

void State::UpdateArray(float dt){
	for(int i = objectArray.size() - 1; i >= 0; --i) {
		objectArray[i].get()->Update(dt);
		if(objectArray[i].get()->IsDead()){
			objectArray.erase(objectArray.begin() + i);
		}
	}
}

void State::RenderArray(){
	if(posInvert != -1){
		for(unsigned int i = 0; i < objectArray.size(); i++) {
			if((int) i != posInvert){
				objectArray[i].get()->Render();
			}
		}
		objectArray[posInvert].get()->Render();
	} else{
		for(unsigned int i = 0; i < objectArray.size(); i++) {
			objectArray[i].get()->Render();
		}
	}
}

bool State::QuitRequested(){
	return quitRequested;
}

bool State::PopRequested(){
	return popRequested;
}

void State::SetPlayer(int x, int y, int type, Rect limits){
	Camera::Unfollow();
	MissionManager::player->SetPosition(x, y);
	if(type != CAMERA_TYPE0 && type != CAMERA_TYPE3) Camera::Follow(MissionManager::player, type);
	else Camera::SetType(type);
	MissionManager::player->SetMovementLimits(limits);
}

void State::RemovePlayer(){
	for(unsigned int i = 0; i < objectArray.size(); i++) {
		if(objectArray[i].get()->Is("Player")){
			//std::cout << "remove " << objectArray.size() << " " << i << std::endl;
			MissionManager::player = (Player*) objectArray[i].release();
			objectArray.erase(objectArray.begin() + i);
			//std::cout << "alive " << objectArray.size() << " " << MissionManager::player->Is("Player") << std::endl;
		}
	}
}

void State::SetPopRequested(){
	popRequested = true;
}

Rect State::GetStateLimits(){
	return limits;
}

void State::RandomState(){
	if(MissionManager::missionManager->randomStates){
		std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<int> distribution(1,6);

		for(unsigned int i = 0; i < objectArray.size(); i++) {
			if(objectArray[i].get()->Is("SceneObject")){
				if(!((SceneObject*) objectArray[i].get())->GetCreateObject()){
					int dice_roll = distribution(generator);
					std::cout << "DICE " << dice_roll << std::endl;
					if(dice_roll <= 2){
						((SceneObject*) objectArray[i].get())->ChangeState();
					}
				}
			}
		}
	}
}
