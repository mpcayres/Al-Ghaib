#include "Mission.hpp"

Mission::Mission() {

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
