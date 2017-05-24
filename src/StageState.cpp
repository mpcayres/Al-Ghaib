#include "PickUpObject.hpp"
#include "StageState.hpp"
#include "InputManager.hpp"
#include "Resources.hpp"
#include "Camera.hpp"
#include "Game.hpp"
#include "Collision.hpp"
#include "Music.hpp"
#include "EndState.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "SceneObject.hpp"
#include "EmptyBox.hpp"

StageState::StageState() : tileSet(64, 64, "img/tileset.png"),
				tileMap("map/tileMap.txt", &tileSet) {

	Player* P = new Player(704, 640);
	EmptyBox* EB = new EmptyBox();
	Enemy* E = new Enemy(300, 200);
	PickUpObject* PO = new PickUpObject(200, 400, "KeyObject", "img/minion.png");
	SceneObject* SO = new SceneObject(800, 200, 1, "img/closedwindow.png");
	objectArray.emplace_back(P);
	objectArray.emplace_back(EB);
	objectArray.emplace_back(E);
	objectArray.emplace_back(PO);
	objectArray.emplace_back(SO);
	Camera::Follow(P);

	music = Music("audio/stageState.ogg");
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
	//music.Play(-1);
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
			if(Collision::IsColliding(objectArray[i].get()->box, objectArray[j].get()->box,
				objectArray[i].get()->rotation*PI/180, objectArray[j].get()->rotation*PI/180)){

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
