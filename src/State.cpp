#include "State.hpp"

State::State(){
	quitRequested = false;
	popRequested = false;
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
		if(objectArray[i].get()->IsDead() == true){
			objectArray.erase(objectArray.begin()+ i);
		}
	}
}

void State::RenderArray(){
	for(int i = objectArray.size() - 1; i >= 0; --i) {
		objectArray[i].get()->Render();
	}
}

bool State::QuitRequested(){
	return quitRequested;
}

bool State::PopRequested(){
	return popRequested;
}
