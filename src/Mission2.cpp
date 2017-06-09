#include "Mission2.hpp"
#include "MissionManager.hpp"

Mission2::Mission2() {
	initialState = "HallState";
	initialX = 450; initialY = 400;
	MissionManager::missionManager->SetPos(initialX, initialY, initialState);
}

Mission2::~Mission2() {

}

void Mission2::Pause(){

}

void Mission2::Resume(){

}

void Mission2::Update(float dt){

}

void Mission2::Render(){

}

void Mission2::SetObjectStage(){

}

void Mission2::SetObjectHall(){

}
