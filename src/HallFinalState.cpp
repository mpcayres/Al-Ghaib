#include "HallFinalState.hpp"
#include "InputManager.hpp"
#include "Camera.hpp"
#include "Collision.hpp"
#include "EmptyBox.hpp"
#include "SceneDoor.hpp"
#include "ScenePortal.hpp"
#include "MovingObject.hpp"
#include "StealthObject.hpp"
#include "SceneUntouchable.hpp"
#include "InventoryBook.hpp"
#include "PickUpObject.hpp"

#include <iostream>

//NESSE STATE TUDO VAI SER SETADO DIRETO NELE
HallFinalState::HallFinalState() :
	State(), tileSet(192, 96, "img/tilesetHallFinal.png"), tileMap("map/tileMapHallFinal.txt", &tileSet) {

	limits = tileMap.FindLimits();
	SetPlayer(50, 310, CAMERA_TYPE2, limits);

	SetInitialObjectArray();

	std::vector<Rect> auxLimits = tileMap.GetInnerLimits();
	for(unsigned i = 0; i < auxLimits.size(); i++){
		MissionManager::player->AddWallLimits(auxLimits[i]);
	}
	objectArray.emplace_back(MissionManager::enemy);
	objectArray.emplace_back(MissionManager::player);
	
	music = Music("audio/boxmusic.wav");

	LoadAssets();
	std::cout << "HFSC2 " << objectArray.size() << std::endl;
}

HallFinalState::~HallFinalState() {
	objectArray.clear();
}

void HallFinalState::Pause(){
	music.Stop();
}

void HallFinalState::Resume(){
	music.Play(-1);
}

void HallFinalState::LoadAssets(){
	background.Open("img/HUD/semired.jpg");
	bg.Open("img/corredor.png");
}

void HallFinalState::Update(float dt){
	InputManager instance = InputManager::GetInstance();

	if(instance.KeyPress(ESCAPE_KEY)){
		EndState();
	}
	if(instance.KeyPress(W_KEY)){
		ChangeState("HallFinalState", "StageState");
	}
	if(instance.KeyPress(Q_KEY)){
		ChangeState("HallState", "StageState");
	}
	quitRequested = instance.QuitRequested();

	Camera::Update(dt);
	UpdateArray(dt);

	int changeIndex = -1;
	posInvert = -1;
	for(int i = objectArray.size() - 1; i >= 0; --i) {
		if(objectArray[i].get()->Is("SceneDoor")){
			if(endGame){
				((SceneDoor*)objectArray[i].get())->SetLock(false);
				((SceneDoor*)objectArray[i].get())->ChangeImage(true);
			}
			if(((SceneDoor*)objectArray[i].get())->GetChangeState()){
				changeIndex = i;
			}
		}
		for(int j = i-1; j >= 0; --j){
			if(Collision::IsColliding(objectArray[i].get()->box, objectArray[j].get()->box,
				objectArray[i].get()->rotation*PI/180, objectArray[j].get()->rotation*PI/180)){

				if(objectArray[i].get()->NotifyCollision(*objectArray[j].get())){
					if(i > posInvert) posInvert = i;
				}
				if(objectArray[j].get()->NotifyCollision(*objectArray[i].get())){
					if(j > posInvert) posInvert = j;;
				}

			}
		}
	}

	if(changeIndex != -1){
		((SceneDoor*)objectArray[changeIndex].get())->SetChangeState(false);
		ChangeState("HallFinalState",
				((SceneDoor*)objectArray[changeIndex].get())->GetDest(), 800, 300, (int) Player::SUL);
	}
}

void HallFinalState::Render(){
	background.Render(0,0,0);
	//bg.Render(0 - Camera::pos.x, Camera::pos.y+33,0);
	tileMap.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	//bg.Render(0,0,0);
	RenderArray();

	if(MissionManager::player->GetShowingInventory()){
		MissionManager::player->RenderInventory();
	} else{
		MissionManager::player->RenderInHand();
		MissionManager::player->RenderNoise();
	}
}

void HallFinalState::SetInitialObjectArray(){
	EmptyBox* EB = new EmptyBox();
	objectArray.emplace_back(EB);

	MovingObject* Banquinho1 = new MovingObject(580, 380, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(Banquinho1);

	MovingObject* Banquinho2 = new MovingObject(900, 380, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(Banquinho2);

	SceneObject* Abajur = new SceneObject(1000, 260, "img/cenario/geral/abajur.png", "");
	objectArray.emplace_back(Abajur);

	MovingObject* Banquinho3 = new MovingObject(1120, 285, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(Banquinho3);

	MovingObject* Banquinho4 = new MovingObject(1300, 285, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(Banquinho4);

	SceneObject* Abajur2 = new SceneObject(1410, 260, "img/cenario/geral/abajur.png", "");
	objectArray.emplace_back(Abajur2);

	MovingObject* Vaso1 = new MovingObject(1760, 369, "img/cenario/geral/vaso.png", false);
	objectArray.emplace_back(Vaso1);

	MovingObject* Vaso2 = new MovingObject(1900, 369, "img/cenario/geral/vaso.png", false);
	objectArray.emplace_back(Vaso2);

	MovingObject* Cadeira = new MovingObject(2320, 280, "img/cenario/geral/cadeira.png", true);
	objectArray.emplace_back(Cadeira);

	StealthObject* Escrivaninha = new StealthObject(2550, 350, "img/cenario/geral/escrivaninha-fechado.png");
	objectArray.emplace_back(Escrivaninha);

	MovingObject* SitJunto = new MovingObject(2570, 420, "img/cenario/sala/banquinho.png", true);
	objectArray.emplace_back(SitJunto);

	SceneObject* Bau1 = new SceneObject(2900, 260, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "InventoryLine", SceneObject::SAMEY_UP);
	objectArray.emplace_back(Bau1);

	SceneObject* Bau2 = new SceneObject(3000, 260, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "InventoryGum", SceneObject::SAMEY_UP);
	objectArray.emplace_back(Bau2);

	SceneObject* Bau3 = new SceneObject(3100, 260, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectArray.emplace_back(Bau3);

	SceneObject* Bau4 = new SceneObject(3200, 260, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectArray.emplace_back(Bau4);

	SceneObject* Bau5 = new SceneObject(3300, 260, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "InventoryNeedle", SceneObject::SAMEY_UP);
	objectArray.emplace_back(Bau5);

	SceneObject* Bau6 = new SceneObject(3400, 260, "img/cenario/geral/bau-fechado.png",
			"img/cenario/geral/bau-aberto.png", 0, 1, 1, "", SceneObject::SAMEY_UP);
	objectArray.emplace_back(Bau6);

	SceneObject* Mesa = new SceneObject(4200, 250, "img/cenario/mae/mesinha.png", "");
	objectArray.emplace_back(Mesa);

	PickUpObject* Livro = new PickUpObject(4245, 285, "InventoryBook", "img/inventario/livro-simbolo.png", false, 0.4, 0.4);
	objectArray.emplace_back(Livro);

	SceneObject* CamaGato = new SceneObject(4700, 280, "img/cenario/corredor/cama-gato.png", "", 0, 0.7, 0.7);
	objectArray.emplace_back(CamaGato);

	SceneObject* Gato1 = new SceneObject(4770, 285, "img/cenario/corredor/pote-com-racao.png", "", 0, 0.7, 0.7);
	objectArray.emplace_back(Gato1);

	SceneObject* Gato2 = new SceneObject(4810, 285, "img/cenario/corredor/pote-sem-racao.png", "", 0, 0.7, 0.7);
	objectArray.emplace_back(Gato2);

	StealthObject* Armario2 = new StealthObject(5500, 210, "img/cenario/geral/armario-corredor-fechado.png");
	objectArray.emplace_back(Armario2);

	SceneDoor* DoorToKidRoom = new SceneDoor(6000, 200, "StageState");
	objectArray.emplace_back(DoorToKidRoom);
}
