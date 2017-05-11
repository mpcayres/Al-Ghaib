#include "StageState.h"
#include "InputManager.h"
#include "Camera.h"
#include "Alien.h"
#include "Penguins.h"
#include "Collision.h"
#include "Game.h"
#include "EndState.h"
#include "StateData.h"

#define NUM_ALIENS 5

StageState::StageState() {
	objectArray.emplace_back( std::unique_ptr<Penguins>(new Penguins(704,640)) );
	Camera::Follow(Penguins::player);

	for(int i = 0; i < NUM_ALIENS; i++){
		objectArray.emplace_back(std::unique_ptr<Alien>( new Alien (
			rand()%MAPLIMIT_W, rand()%MAPLIMIT_H, (rand()%5)+1) ) );
	}

	bg.Open("img/ocean.jpg");
	tileSet = new TileSet(64, 64, "img/tileset.png");
	tileMap = new TileMap("map/tileMap.txt", tileSet);
	music = new Music("audio/stageState.ogg");
}

StageState::~StageState() {
	music->Stop();
	objectArray.clear();
	delete(tileSet);
	delete(tileMap);
	delete(music);
}

void StageState::Update(float dt){
	if(SDL_QuitRequested() || InputManager::GetInstance().QuitRequested()){
		quitRequested = true;
	}
	if(InputManager::GetInstance().KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}

	Camera::Update(dt);
	UpdateArray(dt);
	for(unsigned int i = 0; i < objectArray.size(); i++){
		for(unsigned int j = i + 1; j < objectArray.size(); j++){
			if(Collision::IsColliding(objectArray[i]->box, objectArray[j]->box,
					objectArray[i]->rotation, objectArray[j]->rotation)){
				objectArray[i]->NotifyCollision(*objectArray[j]);
				objectArray[j]->NotifyCollision(*objectArray[i]);
			}
		}
	}

	if(Penguins::player == nullptr){
		popRequested = true;
		StateData stateData;
		stateData.playerVictory = false;
		Game::GetInstance().Push(new EndState(stateData));
	}
	else if (Alien::alienCount <= 0){
		popRequested = true;
		StateData stateData;
		stateData.playerVictory = true;
		Game::GetInstance().Push(new EndState(stateData));
	}
}

void StageState::Render(){
	bg.Render(0, 0);
	tileMap->RenderLayer(0, Camera::pos.x, Camera::pos.y);
	RenderArray();
	tileMap->Render(Camera::pos.x, Camera::pos.y);
}

void StageState::Pause(){
	music->Stop();
}

void StageState::Resume(){
	music->Play(-1);
}
