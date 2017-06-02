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
#include "SceneWindow.hpp"
#include "SceneDoor.hpp"
#include "MovingObject.hpp"
#include "EmptyBox.hpp"
#include "Walls.hpp"

StageState::StageState(std::vector<std::unique_ptr<GameObject>> obj, bool inicial) :
	tileSet(64, 64, "img/tileset.png"), tileMap("map/tileMap.txt", &tileSet) {

	limits = tileMap.FindLimits();
	SetInitialObjectArray();
	//objectArray.emplace_back(std::move(obj));

	music = Music("audio/stageState.ogg");
	quitRequested = false;
	time = Timer();
	flagMorte = false;

	LoadAssets();
}

StageState::~StageState(){
	//Camera::Unfollow();
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
			Camera::Unfollow();
			stateData.playerVictory = false;
			Game::GetInstance().Push(new EndState(stateData));
		}
	}
	if(SceneDoor::GetChangeState()){
		popRequested = true;
		Camera::Unfollow();
		SceneDoor::SetChangeState(false);
		Game::GetInstance().GetMissionManager().ChangeState(std::move(objectArray), "StageState", "HallState");
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
	//tileMap.Render(Camera::pos.x, Camera::pos.y);

	if(Player::player->GetShowingInventory()){
		Player::player->RenderInventory();
	} else{
		Player::player->RenderInHand();
		Player::player->RenderNoise();
	}
}

void StageState::SetInitialObjectArray(){
	Player* P = new Player(600, 400);
	P->SetMovementLimits(limits);
	Camera::Follow(P, CAMERA_TYPE1);

	EmptyBox* EB = new EmptyBox();
	//Walls *Wall = new Walls(700, 400, 100,100);
	Enemy* E = new Enemy(1100, 500);
	SceneDoor* Door = new SceneDoor(800, 200, "img/doorclosed.png", "img/dooropened.png");
	PickUpObject* PO = new PickUpObject(700, 300, "KeyObject", "img/minionbullet1.png");
	SceneWindow* Window = new SceneWindow(500, 200, "img/closedwindow.png", "img/openwindow.png");

	MovingObject* Table = new MovingObject(500, 400, "img/box.png");
	Table->SetMovementLimits(limits);

	objectArray.emplace_back(P);
	objectArray.emplace_back(EB);
	//objectArray.emplace_back(Wall);
	objectArray.emplace_back(E);
	objectArray.emplace_back(PO);
	objectArray.emplace_back(Window);
	objectArray.emplace_back(Door);
	objectArray.emplace_back(Table);
}
