#include "StageState.hpp"
#include "InputManager.hpp"
#include "Resources.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Music.hpp"
#include "EndState.hpp"
#include "Player.hpp"

StageState::StageState() : tileSet(64,64,"img/tileset.png"),
				tileMap("map/tileMap.txt", &tileSet) {

	Player* P = new Player(704, 640);
	objectArray.emplace_back(P);
	Camera::Follow(P);

	music = Music("audio/stageState.ogg");
	music.Play(-1);
	quitRequested = false;
	time = Timer();
	flagMorte = false;

	LoadAssets();
}

StageState::~StageState(){
	objectArray.clear();
}

void StageState::Pause(){
	music.Stop();
}

void StageState::Resume(){
	music.Play(-1);
}

void StageState::LoadAssets(){
	bg.Open("img/ocean.jpg");
}

void StageState::Update(float dt){
	InputManager instance = InputManager::GetInstance();
	time.Update(dt);
	if(instance.KeyPress(ESCAPE_KEY)){
		popRequested = true;
	}
	if(Player::player == nullptr){
		if(flagMorte == false){
			time.Restart();
			flagMorte = true;
		}

		if(time.Get() >= 1.5 && flagMorte == true){
			popRequested = true;
			stateData.playerVictory = false;
			Game::GetInstance().Push(new EndState(stateData));
		}
	}
	quitRequested = instance.QuitRequested();

	Camera::Update(dt);

	UpdateArray(dt);

	for(int i = objectArray.size() - 1; i >= 0; --i) {
		for(int j = i-1; j >= 0; --j){
				if(Collision::IsColliding(objectArray[i].get()->box,objectArray[j].get()->box,
					objectArray[i].get()->rotation, objectArray[j].get()->rotation) == true){
					objectArray[i].get()->NotifyCollision(*objectArray[j].get());
					objectArray[j].get()->NotifyCollision(*objectArray[i].get());
				}
			}
	}
}

void StageState::Render(){
	bg.Render(0,0,0);
	tileMap.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	RenderArray();
	tileMap.Render(Camera::pos.x, Camera::pos.y);
	
}
