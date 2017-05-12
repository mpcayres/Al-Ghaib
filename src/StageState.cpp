#include "Player.hpp"
#include "StageState.hpp"
#include "InputManager.hpp"
#include "Resources.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Music.hpp"
#include "EndState.hpp"

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
	bg.Open("img/minionbullet2.png");
	bg.Open("img/penguinbullet.png");
	bg.Open("img/cubngun.png");
	bg.Open("img/penguin.png");
	bg.Open("img/tileset.png");
	bg.Open("img/minion.png");
	bg.Open("img/alien.png");
	bg.Open("img/minion.png");
	bg.Open("img/miniondeath.png");
	bg.Open("img/penguindeath.png");
	bg.Open("img/aliendeath.png");
	bg.Open("img/ocean.jpg");
}

void StageState::Update(float dt){
	InputManager instance = InputManager::GetInstace();
	//Input();
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
		//std::cout<< "\n i:"<<  i << "\n";
		for(int j = i-1; j >= 0; --j){
			//std::cout<< j << " ";
				if(Collision::IsColliding(objectArray[i].get()->box,objectArray[j].get()->box,
					objectArray[i].get()->rotation, objectArray[j].get()->rotation) == true){
					//	std::cout<< i << " " << j <<"\n";
					objectArray[i].get()->NotifyCollision(*objectArray[j].get());
					objectArray[j].get()->NotifyCollision(*objectArray[i].get());
				}
			}
	}
}

void StageState::Render(){
	bg.Render(0,0,0);
	tileMap.RenderLayer( 0 ,Camera::pos.x,Camera::pos.y);

	RenderArray();

	for(int j = 1; j < tileMap.GetDepth(); j++) {
		tileMap.RenderLayer( j, Camera::pos.x*1.5, Camera::pos.y*1.5);
	}
	
}


