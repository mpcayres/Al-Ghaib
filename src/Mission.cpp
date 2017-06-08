#include "Mission.hpp"

Mission::Mission() {
	popRequested = false;
}

Mission::~Mission() {

}

std::string Mission::GetInitialState(){
	return initialState;
}

std::vector<std::unique_ptr<GameObject>> Mission::GetObjectStage(){
	return std::move(objectStage);
}

std::vector<std::unique_ptr<GameObject>> Mission::GetObjectHall(){
	return std::move(objectHall);
}


bool Mission::PopRequested(){
	return popRequested;
}

bool Mission::QuitRequested(){
	return quitRequested;
}

/*bool Mission::GetDoor(){
	return door;
}

void Mission::SetDoor(bool value){
	door = value;
}*/

