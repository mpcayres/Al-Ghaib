#include "State.h"

State::State() {
	popRequested = false;
	quitRequested = false;
}

State::~State() { }

void State::AddObject(GameObject *ptr){
	objectArray.emplace_back(ptr);
}

bool State::PopRequested(){
	return popRequested;
}

bool State::QuitRequested(){
	return quitRequested;
}

void State::UpdateArray(float dt){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		objectArray[i]->Update(dt);
		if(objectArray[i]->IsDead())
			objectArray.erase(objectArray.begin() + i);
	}
}

void State::RenderArray(){
	for(unsigned int i = 0; i < objectArray.size(); i++){
		if(objectArray[i]->IsDead() == true) continue;
		objectArray[i]->Render();
	}
}
